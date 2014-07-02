#include "ofApp.h"


//--------
void ofApp::setup(){
    
    // set up interface in PORTRAIT mode (or LANDSCAPE)
    controlOsc.setup("example", PORTRAIT);
    
    // create two new pages for interface
    Page* page1 = controlOsc.addPage("page1");
    Page* page2 = controlOsc.addPage("page2");
    
    // make a bunch of widgets
    // supported types at the moment include: BUTTON, MULTIBUTTON, SLIDER, MULTISLIDER

    Widget w1;
    w1.type = BUTTON;
    w1.name = "myButton";
    w1.x    = 0.1;
    w1.y    = 0.3;
    w1.w    = 0.2;
    w1.h    = 0.15;
    
    Widget w2;
    w2.type = SLIDER;
    w2.name = "mySlider";
    w2.x    = 0.1;
    w2.y    = 0.55;
    w2.w    = 0.7;
    w2.h    = 0.1;
    w2.isVertical = false;
    w2.address = "/aDifferentAddress";  // can override osc address
    
    Widget w3;
    w3.type = MULTIBUTTON;
    w3.name = "myMultiButton";
    w3.x    = 0.1;
    w3.y    = 0.3;
    w3.w    = 0.5;
    w3.h    = 0.2;
    w3.nrows = 2;
    w3.ncols = 3;
    
    Widget w4;
    w4.type = MULTISLIDER;
    w4.name = "myMultiSlider";
    w4.x    = 0.1;
    w4.y    = 0.65;
    w4.w    = 0.5;
    w4.h    = 0.2;
    w4.numSliders = 3;
    
    
    // put widgets into pages
    page1->addWidget(w1);
    page1->addWidget(w2);
    page2->addWidget(w3);
    page2->addWidget(w4);
    
    
    // full json string for above-generated interface
    string json = controlOsc.getJson();
    
    
    // the resulting json string can be loaded into ControlOSC.
    // there are two ways of doing this.
    
    // 1) push it directly to ControlOSC by sending the json string via OSC.
    //    Replace myPhoneIpAddress with the current ip address of your phone
    //    and make sure it is connected to the same network as your laptop.
    //    Make sure to run the command only when you have ControlOSC open
    //    on your phone.
    //
    //    Note: There appear to be some bug which cause ControlOSC to
    //    crash on your phone if you attempt to upload an interface
    //    where some of the buttons run javascript commands, which happens
    //    if you have more than 1 page in your interface.  Thus, it is
    //    recommended right now to do it manually using the second approach
    //    if your interface contains more than 1 page.
    
    
    /*
    string myPhoneIpAddress = "192.168.0.1";    // <-- set this to your phone's IP
    controlOsc.uploadToControlP5(myPhoneIpAddress);
    */
    
    
    // 2) save the json string to a file, upload it to the web, and
    //    add the interface manually via ControlOSC.
    
    /*
    string PATH_TO_FILE = "/Users/You/Desktop/myInterface.json";
    controlOsc.saveToFile(PATH_TO_FILE);
    */
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