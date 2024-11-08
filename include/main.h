#ifndef MAIN_H
#define MAIN_H

#include <wx/wx.h>
#include "classes/Graph.h"

class MyApp : public wxApp {
public:
    wxFrame* frame;
    bool OnInit() override;

    static Graph& GetGraph() {
        App_Graph.setVals();
        return App_Graph;
    }

private:
    static Graph App_Graph;
};
#endif