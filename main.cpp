#include <iostream>
#include <string>
#include <fstream>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

int main(int argc, char **argv)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
    json->set("name", "foo");
    json->set("address", "bar");

    std::ostringstream oss;
    Poco::JSON::Stringifier::stringify(json, oss, 4, -1, Poco::JSON_PRESERVE_KEY_ORDER);
    std::ofstream ofs("output.json");
    if (ofs.is_open() == true)
    {
        ofs << oss.str();
        ofs.close();
    }
}
