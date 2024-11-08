#include <wx/wx.h>
#include "frames/StartupFrame.h"
#include "classes/Graph.h"
#include "main.h"

using namespace std;


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {

    StartupFrame *frame = new StartupFrame();
    frame->SetSize(800,600);
    frame->Center();
    frame->Maximize();
    frame->Show(true);
    return true;
}
