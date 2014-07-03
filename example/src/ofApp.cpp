#include "ofApp.h"


//--------
void ofApp::setup(){
    
    // create an interface
    
    controlOsc.setup("example", PORTRAIT);
    Page* page = controlOsc.addPage("page1");
    
    page->addButton("myButton", 0.05, 0.1, 0.2, 0.1);
    page->addToggle("myToggle", 0.27, 0.1, 0.2, 0.1);

    page->addMultiButton("myMultiButton", 0.05, 0.3, 0.25, 0.25, 3, 2);
    page->addMultiToggle("myMultiToggle", 0.4, 0.3, 0.25, 0.25, 2, 2);
    
    ofxControlOSCSlider *slider = page->addSlider("mySlider", 0.5, 0.1, 0.4, 0.1);
    slider->setAddress("/myCustomAddress");
    slider->setColors("#0f0", "#f00");
    
    
    string json = controlOsc.getJson();
    cout << json << endl;
    
    // The string json contains the interface. There are two ways to
    // get it onto your device. The manual way is to save it to a file
    // and upload it to a webserver, from which you can retrieve it
    // inside the ControlOSC application.
    // Save it using controlOsc.save(PATH_TO_YOUR_FILE) or output
    // the json string manually using controlOsc.getJson()

    
    
    // The second way is to push the json directly to your phone over OSC.
    // Make sure your android device is connected to the same network as your
    // computer before running, and make sure ControlOSC is open.
    // Set myPhoneIpAddress to the network address of your device.
    // This feature is unstable however, as it causes ControlOSC
    // to crash sometimes depending on the features added. So if it doesn't
    // work, you should use the above manual way
    
    string ipAddress = "192.168.1.105";    // <-- change to your phone's IP
    ofxOscSender osc;
    ofxOscMessage m;
    m.setAddress("/pushInterface");
    m.addStringArg(json);
    osc.setup(ipAddress, 8080);     // port must always be 8080
    osc.sendMessage(m);
}

//--------
void ofApp::update(){
}

//--------
void ofApp::draw(){
}

//--------
void ofApp::keyPressed(int key){
}