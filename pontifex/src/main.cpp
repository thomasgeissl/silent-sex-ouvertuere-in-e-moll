#include "ofAppNoWindow.h"
#include "ofApp.h"
#include "ofxCommandLineUtils.h"

// ./bin/example-commandlineargs.app/Contents/MacOS/example-commandlineargs -v -d -p 8000 -h localhost

int main(int argc, char *argv[])
{
    cxxopts::Options options("pontifex", "OSC to MIDI bridge for silent sex ouvertuere in e moll performance");
    options.add_options()("d,debug", "Enable debugging")("l,list", "list", cxxopts::value<bool>()->default_value("false"))("m,midiport", "midiport", cxxopts::value<int>()->default_value("0"));
    auto result = options.parse(argc, argv);

    ofAppNoWindow window;
    ofSetupOpenGL(&window, 640, 480, OF_WINDOW);

    auto app = new ofApp(result["m"].as<int>());
    if (result["l"].as<bool>())
    {
        app->listPorts();
        return 0;
    }
    return ofRunApp(app);
}