#include "XmlParser.h"

XmlParser::XmlParser() 
{
  std::map<std::string, void(*)(std::string componentData, flecs::entity& entity)> mapa = {
    std::pair<std::string, void(*)(std::string, flecs::entity&)>{ "Position",& AddNewComponent<Position, ThreeFloats> },
  { "Velocity", &AddNewComponent<Velocity, ThreeFloats> },
  { "Gravity", &AddNewComponent<Gravity, ThreeFloats> },
  { "BouncePlane", &AddNewComponent<BouncePlane, FourFloats> },
  { "Bounciness", &AddNewComponent<Bounciness, float> },
  { "ShiverAmount", &AddNewComponent<ShiverAmount, float>},
  { "FrictionAmount", &AddNewComponent<FrictionAmount, float>},
  { "Speed", &AddNewComponent<Speed, float>},

  { "CubeMesh", &AddNewComponent<CubeMesh, Tag> },

  { "Controllable", &AddNewComponent<Controllable, Tag> },
  { "JumpSpeed", &AddNewComponent<JumpSpeed, float> }
  };

  ComponentNamesMap = std::move(mapa);
}

void XmlParser::ParseDocument(const std::string& filename, flecs::world& world)
{
  tinyxml2::XMLDocument doc;
  auto error = doc.LoadFile(filename.c_str());
  auto root = doc.FirstChildElement();
  ParseEntities(root->FirstChildElement(_entityElementName), world);
}

void XmlParser::ParseEntities(const tinyxml2::XMLElement * startElement, flecs::world& world)
{
  const tinyxml2::XMLElement* currentElement = startElement;
  while (currentElement != nullptr)
  {
    ParseEntity(currentElement, world);
    currentElement = currentElement->NextSiblingElement(_entityElementName);
  }
}

void  XmlParser::ParseEntity(const tinyxml2::XMLElement * entityElement, flecs::world& world)
{
  auto newEntity = world.entity();
  // = flecs.entity(&world, name);
  auto componentElement = entityElement->FirstChildElement();
  while (componentElement != nullptr)
  {
    ParseComponent(componentElement, newEntity);
    componentElement = componentElement->NextSiblingElement();
  }
}

void XmlParser::ParseComponent(const tinyxml2::XMLElement* componentElement, flecs::entity& entity)
{
  auto currentComponent = componentElement->FirstAttribute();
  while (currentComponent != nullptr)
  {
    ComponentNamesMap[currentComponent->Name()](std::string(currentComponent->Value()), entity);
    currentComponent = currentComponent->Next();
  }
}
