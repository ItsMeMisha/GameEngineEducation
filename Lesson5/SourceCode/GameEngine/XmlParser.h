#pragma once

#include <tinyxml2.h>
#include <flecs.h>

#include <string>
#include <map>
#include <array>

#include "EntitySystem/ComponentDataTypes.h"

template<int N>
std::array<float, N> ParseNFloats(std::string src, const std::string& devider);

class XmlParser
{
public:
  XmlParser();
  void ParseDocument(const std::string& filename, flecs::world& world);

private:
  void ParseEntities(const tinyxml2::XMLElement* startElement, flecs::world& world);
  void ParseEntity(const tinyxml2::XMLElement* entityElement, flecs::world& world);
  void ParseComponent(const tinyxml2::XMLElement* componentElement, flecs::entity& entity);

  template<typename T, typename DataType>
  static void AddNewComponent(std::string componentData, flecs::entity& entity);

  template<typename T, typename DataType>
  struct AddNewComponent_impl
  {
    static void act(std::string & componentData, flecs::entity& entity);
  };

  std::map<std::string, void(*)(std::string componentData, flecs::entity& entity)> ComponentNamesMap;
  const char* _entityElementName = "entity";
};

template<typename T, typename DataType>
void XmlParser::AddNewComponent(std::string componentData, flecs::entity& entity)
{
  AddNewComponent_impl<T, DataType>::act(componentData, entity);
}

template<typename T, typename DataType>
void XmlParser::AddNewComponent_impl<T, DataType>::act(std::string & componentData, flecs::entity& entity)
{
  //Unspecified DataType, add as tag
  entity.add<T>();
}

template<typename T>
struct XmlParser::AddNewComponent_impl<T, ThreeFloats> {
  static void act(std::string& componentData, flecs::entity& entity)
  {
    auto values = ParseNFloats<3>(componentData, ",");
    entity.set(T{ values[0], values[1], values[2] });
  }
};

template<typename T>
struct XmlParser::AddNewComponent_impl<T, FourFloats> {
  static void act(std::string & componentData, flecs::entity& entity)
  {
    auto values = ParseNFloats<4>(componentData, ",");
    entity.set(T{ values[0], values[1], values[2], values[3]});
  }
};

template<typename T>
struct XmlParser::AddNewComponent_impl<T, float> {
  static void act(std::string & componentData, flecs::entity& entity)
  {
    char* endptr = nullptr;
    float value = std::strtof(componentData.c_str(), &endptr);
    entity.set(T{ value });
  }
};

template<typename T>
struct XmlParser::AddNewComponent_impl<T, std::string> {
  static void act(std::string & componentData, flecs::entity& entity)
  {
    std::string str(componentData);
    entity.set(T{ str });
  }
};

template<typename T>
struct XmlParser::AddNewComponent_impl<T, Tag> {
  static void act(std::string & componentData, flecs::entity& entity)
  {
    entity.add<T>();
  }
};

template<int N>
inline std::array<float, N> ParseNFloats(std::string src, const std::string& devider)
{
  std::array<float, N> results;
  char* end;
  for (int i = 0; i < N; ++i)
  {
    int currentEnd = src.find(devider);
    std::string toTransform = src.substr(0, currentEnd);
    results[i] = std::strtof(toTransform.c_str(), &end);
    src.erase(0, toTransform.length() + devider.length());
  }

  return results;
}
