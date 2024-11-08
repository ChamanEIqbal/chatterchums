Documentation & Acknowledgements
================================

Social Media Application in C++, using wxWidgets & sqlite3 database, is a project that was submitted to [redacted] for the CCA (Complex Computing Activity) of our Data Structures and Algorithms course (CSL-221).

Authors:
--------

* Mustafa Ahmed Khan *

  

Modules
=======

* GUI
    ---
    
    * ### Dashboard.h _(../include/frames/Dashboard.h)_
        
        * **Add Posts** _(../include/components/AddPostPanel.h)_
        * **View Posts** _(../include/componentsAllPostsPane.h)_
        * **Friend Recommendation** _(../include/components/FriendsPanel.h)_
        * **User Profile** _(../components/ProfilePanel.h)_
* Frames
    ------
    
    * **Login Frame** _(../src/LoginFrame.cpp & ../include/frames/LoginFrame.h)_
    * **Register Frame** _(../src/RegFrame.cpp & ../include/frames/RegFrame.h)_
    * **Startup Frame** _(../src/StartupFrame.cpp & ../include/frames/StartupFrame.h)_
* Database (Data Access Objects)
    ------------------------------
    
    * **Friends Table Data Access Object** _(../include/database/friendsDao.h)_
    * **Users Table Data Access Object** _(../include/database/userDao.h)_
    * **Posts Table Data Access Object** _(../include/database/postDao.h)_
* Data Structures Classes
    -----------------------
    
    * **Graph** _(../include/classes/Graph.h)_
    * **User** _(../include/classes/User.h)_
    * **Post** _(../include/classes/Post.h)_  
          
          
        

Explanation of Graph Implementation:
====================================

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
    
    

MyApp Class _(../include/main.h)_, has an instantiation of Graph.h, as a singleton instance, which can be called anywhere. when the **GetGraph()** function is called, it initalizes the value of the _unordered_map_ instance of the Graph's class from the database, and sets its values from the FRIENDS table (../resources/database.db).

It is called in the Dashboard's Implementation as follows:

    /*ADD FRIENDS PANEL*/
    Graph graph = MyApp::GetGraph();
    FriendsPanel *add_friends_panel = new FriendsPanel(notebook, user, graph);
    notebook->AddPage(add_friends_panel, wxString::Format("Friends"));
    /*Add FRIENDS PANEL END */
    

LINE NO. 45 ONWARDS _(../include/frames/Dashboard.h)_

The graph is then given to the FriendsPanel's constructor for further implementation.

    vector<string> recommended = dao_user.getUsernamesFromIds(Graph.dfsRecommendation(user_.id, 15));
    
    for (int i = 0; i < recommended.size(); ++i) {  
    wxPanel* squarePanel = CreateSquarePanel(scrolledWindow2, recommended[i]);
    scrolledBoxSizer2->Add(squarePanel, 0, wxALL, 10);
    }
    

We can change the .dfsRecommendation() to .bfsRecommendation, though done manually; it would have been better if we were to add an option.

The DAO_USER instance uses a function as follows, which allows the vector of integers to be correlated one by one to each ID of the user in the USERS table, and return an array of strings containing its corresponding username.

    std::vector<std::string> getUsernamesFromIds(std::vector<int> userIDs) {
    std::vector<std::string> usernames;
    
    try {
    if (db == nullptr) {
    std::cout << "Error: Database connection is not open. us4" << std::endl;
    return usernames;  // Return an empty vector since there's an error
    }
    
    std::string query = "SELECT UserName FROM USERS WHERE UserId = ?";
    sqlite3_stmt* statement;
    
    // Prepare the statement outside the loop
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
    std::cout << "Error: could not prepare select query." << std::endl;
    return usernames;  // Return an empty vector since there's an error
    }
    
    for (int userID : userIDs) {
    // Bind the parameter
    if (sqlite3_bind_int(statement, 1, userID) != SQLITE_OK) {
      std::cout << "Error: could not bind parameter." << std::endl;
      return usernames;  // Return an empty vector since there's an error
    }
    
    // Execute the statement
    int stepResult = sqlite3_step(statement);
    
    if (stepResult == SQLITE_ROW) {
      const char* usernameCStr = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
      std::string retrievedUsername(usernameCStr != nullptr ? usernameCStr : "");
      usernames.push_back(retrievedUsername);
    } else if (stepResult != SQLITE_DONE) {
      std::cout << "Error executing the select query." << std::endl;
      return usernames;  // Return an empty vector since there's an error
    }
    
    sqlite3_reset(statement);
    }
    
    sqlite3_finalize(statement);
    
    } catch (const std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return usernames;
    }
    

Acknowledgements
================

We acknowledge our teachers, for they have given us an opportunity and entrusted us with such a challenging task; We thrived to make them content and We always want them to see in us potential, if it not were for their support; We would not have finished this project with such excellency.

We would also like to give courtesy to [Yanson Tech](https://youtu.be/tHMGA0jIl3Y?si=SAqZZxF3-pNXq1JR), as they introduced us to the concepts of makefiles, external libraries and how headerfiles are created and used in Visual Studio Code.

* * *
