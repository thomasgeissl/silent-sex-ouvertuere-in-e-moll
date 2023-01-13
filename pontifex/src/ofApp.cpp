#include "ofApp.h"

ofApp::ofApp(int midiPort) : _port(9010), _midiPort(midiPort) {}
void ofApp::setup()
{
    ofSetFrameRate(60);
    _receiver.setup(_port);
    if (_midiPort < _midiOut.getNumOutPorts())
    {
        _midiOut.openPort(_midiPort);
    }
    else
    {
        ofLogError() << "invalid port index";
        listPorts();
        ofExit();
    }
    _virtualMidiOut.openVirtualPort("pontifex");
}
void ofApp::update()
{
    while (_receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        _receiver.getNextMessage(m);
        if (m.getAddress() == "/kls/io/crank")
        {
            auto value = m.getArgAsFloat(0);
            ofLogNotice() << "/kls/io/crank " << value;
            _midiOut.sendControlChange(1, 2, (int)(value));
            _virtualMidiOut.sendControlChange(1, 2, (int)(value));
        }
    }
}

void ofApp::listPorts()
{
    _midiOut.listOutPorts();
}