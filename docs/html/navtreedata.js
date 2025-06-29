/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Zappy documentation", "index.html", [
    [ "GitHub Commit Standards Guide - Zappy Project", "md_docs_COMMITS_POLICY.html", [
      [ "Table of Contents", "md_docs_COMMITS_POLICY.html#autotoc_md1", null ],
      [ "Introduction", "md_docs_COMMITS_POLICY.html#autotoc_md2", null ],
      [ "Commit message format", "md_docs_COMMITS_POLICY.html#autotoc_md3", [
        [ "Basic rules", "md_docs_COMMITS_POLICY.html#autotoc_md4", null ]
      ] ],
      [ "Commit types", "md_docs_COMMITS_POLICY.html#autotoc_md5", [
        [ "Main types (Conventional Commits)", "md_docs_COMMITS_POLICY.html#autotoc_md6", null ]
      ] ]
    ] ],
    [ "Zappy Protocols Documentation", "md_docs_PROTOCOLS_DOCUMENTATION.html", [
      [ "Table of Contents", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md8", null ],
      [ "AI Client/Server Protocol", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md10", [
        [ "Connection Process", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md11", null ],
        [ "Client Commands", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md12", null ],
        [ "Server Notifications to Clients", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md13", null ],
        [ "Resources and Objects", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md14", null ],
        [ "Elevation Requirements", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md15", null ]
      ] ],
      [ "GUI Client/Server Protocol", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md17", [
        [ "Connection", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md18", null ],
        [ "Protocol Symbols", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md19", null ],
        [ "Commands and Responses", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md20", [
          [ "Map Information", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md21", null ],
          [ "Player Actions", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md22", null ],
          [ "Incantation", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md23", null ],
          [ "Eggs", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md24", null ],
          [ "Server Control", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md25", null ]
        ] ]
      ] ],
      [ "Server Internal Commands", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md27", [
        [ "Information Commands", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md28", [
          [ "all", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md29", null ],
          [ "status", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md30", null ]
        ] ],
        [ "Client Management", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md31", [
          [ "clients", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md32", null ],
          [ "client", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md33", null ],
          [ "kick", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md34", null ]
        ] ],
        [ "Team Management", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md35", [
          [ "teams", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md36", null ],
          [ "team", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md37", null ],
          [ "fork", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md38", null ]
        ] ],
        [ "Player Management", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md39", [
          [ "players", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md40", null ],
          [ "player", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md41", null ],
          [ "level", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md42", null ],
          [ "inventory", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md43", null ],
          [ "orientation", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md44", null ],
          [ "tp", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md45", null ]
        ] ],
        [ "World Management", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md46", [
          [ "map", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md47", null ],
          [ "tile", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md48", null ],
          [ "frequency", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md49", null ]
        ] ],
        [ "Communication Commands", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md50", [
          [ "broadcast", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md51", null ],
          [ "send_ai", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md52", null ],
          [ "send_gui", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md53", null ]
        ] ],
        [ "Debug and Control Commands", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md54", [
          [ "pause", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md55", null ],
          [ "debug_mode", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md56", null ],
          [ "extra_logs", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md57", null ],
          [ "infinite_food", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md58", null ],
          [ "no_refill", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md59", null ]
        ] ],
        [ "Utility Commands", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md60", [
          [ "help", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md61", null ],
          [ "clear", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md62", null ],
          [ "quit", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md63", null ]
        ] ]
      ] ],
      [ "Notes", "md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md65", null ]
    ] ],
    [ "Zappy GUI", "md_gui_README.html", [
      [ "Description", "md_gui_README.html#autotoc_md67", null ],
      [ "Game Overview", "md_gui_README.html#autotoc_md68", null ],
      [ "Usage", "md_gui_README.html#autotoc_md69", [
        [ "Parameters", "md_gui_README.html#autotoc_md70", null ],
        [ "Example", "md_gui_README.html#autotoc_md71", null ]
      ] ],
      [ "Features", "md_gui_README.html#autotoc_md72", null ],
      [ "Communication Protocol", "md_gui_README.html#autotoc_md73", [
        [ "Main Messages Received", "md_gui_README.html#autotoc_md74", null ],
        [ "Commands Sent to Server", "md_gui_README.html#autotoc_md75", null ]
      ] ]
    ] ],
    [ "🗺️ Zappy 🎮", "md_README.html", [
      [ "Table of contents 📑", "md_README.html#autotoc_md77", null ],
      [ "Description 📝", "md_README.html#autotoc_md78", null ],
      [ "Usage ⚔️", "md_README.html#autotoc_md79", [
        [ "AI", "md_README.html#autotoc_md80", null ],
        [ "GUI", "md_README.html#autotoc_md81", null ],
        [ "SERVER", "md_README.html#autotoc_md82", null ]
      ] ],
      [ "Result 🚩", "md_README.html#autotoc_md83", [
        [ "Defense", "md_README.html#autotoc_md84", null ]
      ] ],
      [ "Compilation 🛠️", "md_README.html#autotoc_md85", [
        [ "Compiling the project", "md_README.html#autotoc_md86", null ],
        [ "Unit tests", "md_README.html#autotoc_md87", null ],
        [ "Cleaning the project", "md_README.html#autotoc_md88", null ]
      ] ],
      [ "Documentation 📚", "md_README.html#autotoc_md89", null ],
      [ "Organisation 📦", "md_README.html#autotoc_md90", null ],
      [ "Contributors 👥", "md_README.html#autotoc_md91", null ]
    ] ],
    [ "Zappy Server", "md_resources_README.html", [
      [ "Usage", "md_resources_README.html#autotoc_md93", null ],
      [ "AI protocol", "md_resources_README.html#autotoc_md94", null ],
      [ "GUI protocol", "md_resources_README.html#autotoc_md95", null ],
      [ "Informations", "md_resources_README.html#autotoc_md96", [
        [ "Incantations", "md_resources_README.html#autotoc_md97", null ]
      ] ],
      [ "Bonus", "md_resources_README.html#autotoc_md98", [
        [ "Server commands", "md_resources_README.html#autotoc_md99", null ]
      ] ]
    ] ],
    [ "Zappy", "md_website_README.html", [
      [ "Prerequisites", "md_website_README.html#autotoc_md101", null ],
      [ "Installation", "md_website_README.html#autotoc_md102", [
        [ "1. Install dependencies", "md_website_README.html#autotoc_md103", null ],
        [ "2. Environment variables configuration", "md_website_README.html#autotoc_md104", null ]
      ] ],
      [ "Available Scripts", "md_website_README.html#autotoc_md105", [
        [ "Development", "md_website_README.html#autotoc_md106", null ],
        [ "Build", "md_website_README.html#autotoc_md107", null ]
      ] ],
      [ "Configuration", "md_website_README.html#autotoc_md108", [
        [ "Environment Variables", "md_website_README.html#autotoc_md109", null ]
      ] ],
      [ "Troubleshooting", "md_website_README.html#autotoc_md110", [
        [ "Port Error", "md_website_README.html#autotoc_md111", null ]
      ] ]
    ] ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Structure Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", null ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "Globals", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", "globals_func" ],
        [ "Variables", "globals_vars.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"Algo_8hpp_source.html",
"classGui_1_1ModelInfo.html#a4c1152c7f6d1e4c4d9adcb73baeea8fc",
"commands__server_8h.html#aba477d297bf55949ae2fa5777f7ad1f6",
"functions_8h.html#ab934cd66c3f8d6db4aabb34eb6622e71",
"md_docs_PROTOCOLS_DOCUMENTATION.html#autotoc_md13",
"my__push__back__circled_8c.html#a5cb860f25a1b43b8bb526f12ba4bfe42",
"server__data__structures_8h.html#a0946e64c8ac05ac1c9740a2375232cebad0611de6f28d4a9c9eac959f5344698e",
"structstr__to__array__s.html#af2219315fc4b9e6a03fe9a07af1493a6"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';