"function convertToId(search)\n"
"{\n"
"  var result = '';\n"
"  for (i=0;i<search.length;i++)\n"
"  {\n"
"    var c = search.charAt(i);\n"
"    var cn = c.charCodeAt(0);\n"
"    if (c.match(/[a-z0-9]/))\n"
"    {\n"
"      result+=c;\n"
"    }\n"
"    else if (cn<16) \n"
"    {\n"
"      result+=\"_0\"+cn.toString(16);\n"
"    }\n"
"    else \n"
"    {\n"
"      result+=\"_\"+cn.toString(16);\n"
"    }\n"
"  }\n"
"  return result;\n"
"}\n"
"\n"
"function getXPos(item)\n"
"{\n"
"  var x = 0;\n"
"  if (item.offsetWidth)\n"
"  {\n"
"    while (item && item!=document.body)\n"
"    {\n"
"      x   += item.offsetLeft;\n"
"      item = item.offsetParent;\n"
"    }\n"
"  }\n"
"  return x;\n"
"}\n"
"\n"
"function getYPos(item)\n"
"{\n"
"  var y = 0;\n"
"  if (item.offsetWidth)\n"
"  {\n"
"     while (item && item!=document.body)\n"
"     {\n"
"       y   += item.offsetTop;\n"
"       item = item.offsetParent;\n"
"     }\n"
"  }\n"
"  return y;\n"
"}\n"
"\n"
"/* A class handling everything associated with the search panel.\n"
"\n"
"   Parameters:\n"
"   name - The name of the global variable that will be \n"
"          storing this instance.  Is needed to be able to set timeouts.\n"
"   resultPath - path to use for external files\n"
"*/\n"
"function SearchBox(name, resultsPath, inFrame)\n"
"{\n"
"  if (!name || !resultsPath) {  alert(\"Missing parameters to SearchBox.\"); }\n"
"   \n"
"  // ---------- Instance variables\n"
"  this.name                  = name;\n"
"  this.resultsPath           = resultsPath;\n"
"  this.keyTimeout            = 0;\n"
"  this.keyTimeoutLength      = 500;\n"
"  this.closeSelectionTimeout = 300;\n"
"  this.lastSearchValue       = \"\";\n"
"  this.lastResultsPage       = \"\";\n"
"  this.hideTimeout           = 0;\n"
"  this.searchTopic           = \"all\";\n"
"  this.searchActive          = false;\n"
"  this.insideFrame           = inFrame;\n"
"\n"
"  // ----------- DOM Elements\n"
"\n"
"  this.DOMSearchField = function()\n"
"  {  return document.getElementById(\"MSearchField\");  }\n"
"\n"
"  this.DOMSearchSelect = function()\n"
"  {  return document.getElementById(\"MSearchSelect\");  }\n"
"\n"
"  this.DOMSearchSelectWindow = function()\n"
"  {  return document.getElementById(\"MSearchSelectWindow\");  }\n"
"\n"
"  this.DOMPopupSearchResults = function()\n"
"  {  return document.getElementById(\"MSearchResults\");  }\n"
"\n"
"  this.DOMPopupSearchResultsWindow = function()\n"
"  {  return document.getElementById(\"MSearchResultsWindow\");  }\n"
"\n"
"  this.DOMSearchResultWindowClose = function()\n"
"  {  return document.getElementById(\"MSearchResultsWindowClose\"); }\n"
"\n"
"  this.DOMSearchBox = function()\n"
"  {  return document.getElementById(\"MSearchBox\");  }\n"
"\n"
"  // ------------ Event Handlers\n"
"\n"
"  // Called when focus is added or removed from the search field.\n"
"  this.OnSearchFieldFocus = function(isActive)\n"
"  {\n"
"    this.Activate(isActive);\n"
"  }\n"
"\n"
"  this.OnSearchSelectShow = function()\n"
"  {\n"
"    var searchSelectWindow = this.DOMSearchSelectWindow();\n"
"    var searchField        = this.DOMSearchSelect();\n"
"\n"
"    if (this.insideFrame)\n"
"    {\n"
"      var left = getXPos(searchField);\n"
"      var top  = getYPos(searchField);\n"
"      left += searchField.offsetWidth + 6;\n"
"      top += searchField.offsetHeight;\n"
"\n"
"      // show search selection popup\n"
"      searchSelectWindow.style.display='block';\n"
"      left -= searchSelectWindow.offsetWidth;\n"
"      searchSelectWindow.style.left =  left + 'px';\n"
"      searchSelectWindow.style.top  =  top  + 'px';\n"
"    }\n"
"    else\n"
"    {\n"
"      var left = getXPos(searchField);\n"
"      var top  = getYPos(searchField);\n"
"      top += searchField.offsetHeight;\n"
"\n"
"      // show search selection popup\n"
"      searchSelectWindow.style.display='block';\n"
"      searchSelectWindow.style.left =  left + 'px';\n"
"      searchSelectWindow.style.top  =  top  + 'px';\n"
"    }\n"
"\n"
"    // stop selection hide timer\n"
"    if (this.hideTimeout) \n"
"    {\n"
"      clearTimeout(this.hideTimeout);\n"
"      this.hideTimeout=0;\n"
"    }\n"
"    return false; // to avoid \"image drag\" default event\n"
"  }\n"
"\n"
"  this.OnSearchSelectHide = function()\n"
"  {\n"
"    this.hideTimeout = setTimeout(this.name +\".CloseSelectionWindow()\",\n"
"                                  this.closeSelectionTimeout);\n"
"  }\n"
"\n"
"  // Called when the content of the search field is changed.\n"
"  this.OnSearchFieldChange = function()\n"
"  {\n"
"    if (this.keyTimeout) // kill running timer\n"
"    {\n"
"      clearTimeout(this.keyTimeout);\n"
"      this.keyTimeout = 0;\n"
"    }\n"
"\n"
"    // strip whitespaces\n"
"    var searchValue = this.DOMSearchField().value.replace(/ +/g, \"\");\n"
"\n"
"    if (searchValue != this.lastSearchValue) // search value has changed\n"
"    {\n"
"      if (searchValue != \"\") // non-empty search\n"
"      {\n"
"        // set timer for search update\n"
"        this.keyTimeout = setTimeout(this.name + '.Search()',\n"
"                                     this.keyTimeoutLength);\n"
"      }\n"
"      else // empty search field\n"
"      {\n"
"        this.DOMPopupSearchResultsWindow().style.display = 'none';\n"
"        this.lastSearchValue = '';\n"
"      }\n"
"    }\n"
"  }\n"
"\n"
"  // Called when an search filter selection is made.\n"
"  // set item with index id as the active item\n"
"  this.OnSelectItem = function(id,topic)\n"
"  {\n"
"    var i,j=0;\n"
"    var win=this.DOMSearchSelectWindow(); \n"
"    for (i=0;i<win.childNodes.length;i++)\n"
"    {\n"
"      var child = win.childNodes[i]; // get span within a\n"
"      if (child.className=='SelectItem')\n"
"      {\n"
"        var node = child.firstChild;\n"
"	if (j==id)\n"
"	{\n"
"          // add a tickmark: see http://doogalbellend.blogspot.com/2007/05/even-more-on-tick-marks-in-html.html\n"
"          node.innerHTML='&bull;';\n"
"        } \n"
"        else\n"
"        {\n"
"          node.innerHTML='&nbsp;';\n"
"        }\n"
"        j++;\n"
"      }\n"
"    }\n"
"    if (topic)\n"
"    {\n"
"      this.searchTopic = topic;\n"
"      var searchValue = this.DOMSearchField().value.replace(/ +/g, \"\");\n"
"      if (searchValue != \"\" && this.searchActive) // something was found -> do a search\n"
"      {\n"
"        this.Search();\n"
"      }\n"
"    }\n"
"    else\n"
"    {\n"
"      this.Activate(false);\n"
"    }\n"
"  }\n"
"\n"
"  this.OnCloseHighlight = function(active)\n"
"  {\n"
"    var close = this.DOMSearchResultWindowClose();\n"
"    if (active)\n"
"    {\n"
"      close.firstChild.src = this.resultsPath + '/close_active.png';\n"
"    }\n"
"    else\n"
"    {\n"
"      close.firstChild.src = this.resultsPath + '/close.png';\n"
"    }\n"
"    return false;\n"
"  }\n"
"\n"
"  // --------- Actions\n"
"\n"
"  // Closes the results window.\n"
"  this.CloseResultsWindow = function()\n"
"  {\n"
"    this.DOMPopupSearchResultsWindow().style.display = \"none\";\n"
"    this.Activate(false);\n"
"  }\n"
"\n"
"  this.CloseSelectionWindow = function()\n"
"  {\n"
"    this.DOMSearchSelectWindow().style.display = \"none\";\n"
"  }\n"
"\n"
"  // Performs a search.\n"
"  this.Search = function()\n"
"  {\n"
"    this.keyTimeout = 0;\n"
"\n"
"    // strip leading whitespace\n"
"    var searchValue = this.DOMSearchField().value.replace(/^ +/, \"\");\n"
"\n"
"    var code = searchValue.toLowerCase().charCodeAt(0);\n"
"    var hexCode;\n"
"    if (code<16) \n"
"    {\n"
"      hexCode=\"0\"+code.toString(16);\n"
"    }\n"
"    else \n"
"    {\n"
"      hexCode=code.toString(16);\n"
"    }\n"
"\n"
"    var resultsPage;\n"
"    var resultsPageWithSearch;\n"
"    var hasResultsPage;\n"
"\n"
"    // indexSectionsWithContent is defined in searchdata.js\n"
"    if (indexSectionsWithContent[this.searchTopic].charAt(code-32) == '1')\n"
"    {\n"
"       resultsPage = this.resultsPath + '/' + this.searchTopic + '_' + hexCode + '.html';\n"
"       resultsPageWithSearch = resultsPage+'?'+escape(searchValue);\n"
"       hasResultsPage = true;\n"
"    }\n"
"    else // nothing available for this search term\n"
"    {\n"
"       resultsPage = this.resultsPath + '/nomatches.html';\n"
"       resultsPageWithSearch = resultsPage;\n"
"       hasResultsPage = false;\n"
"    }\n"
"\n"
"    window.frames.MSearchResults.location.href = resultsPageWithSearch;  \n"
"    var domPopupSearchResultsWindow = this.DOMPopupSearchResultsWindow();\n"
"\n"
"    if (domPopupSearchResultsWindow.style.display!=\"block\")\n"
"    {\n"
"       if (this.insideFrame)\n"
"       {\n"
"         var domSearchBox = this.DOMSearchBox();\n"
"         var domPopupSearchResults = this.DOMPopupSearchResults();\n"
"         this.DOMSearchResultWindowClose().style.textAlign = 'left';\n"
"         domPopupSearchResultsWindow.style.position = 'relative';\n"
"         domPopupSearchResultsWindow.style.display  = 'block';\n"
"         var width = document.body.clientWidth - 8; // the -8 is for IE :-(\n"
"         domPopupSearchResultsWindow.style.width    = width + 'px';\n"
"         domPopupSearchResults.style.width          = width + 'px';\n"
"       }\n"
"       else\n"
"       {\n"
"         var domSearchField = this.DOMSearchField();\n"
"         var domPopupSearchResults = this.DOMPopupSearchResults();\n"
"         var left = getXPos(domSearchField) + domSearchField.offsetWidth;\n"
"         var top  = getYPos(domSearchField) + domSearchField.offsetHeight + 1;\n"
"         domPopupSearchResultsWindow.style.display = 'block';\n"
"         left -= domPopupSearchResults.offsetWidth;\n"
"         domPopupSearchResultsWindow.style.top     = top  + 'px';\n"
"         domPopupSearchResultsWindow.style.left    = left + 'px';\n"
"       }\n"
"    }\n"
"\n"
"    this.lastSearchValue = searchValue;\n"
"    this.lastResultsPage = resultsPage;\n"
"  }\n"
"\n"
"  // -------- Activation Functions\n"
"\n"
"  // Activates or deactivates the search panel, resetting things to \n"
"  // their default values if necessary. \n"
"  this.Activate = function(isActive)\n"
"  {\n"
"    if (isActive || // open it\n"
"        this.DOMPopupSearchResultsWindow().style.display == 'block' \n"
"       )\n"
"    {\n"
"      this.DOMSearchBox().className = 'MSearchBoxActive';\n"
"\n"
"      var searchField = this.DOMSearchField();\n"
"\n"
"      if (searchField.value == 'Search') // clear \"Search\" term upon entry\n"
"      {  \n"
"        searchField.value = '';  \n"
"        this.searchActive = true;\n"
"      }\n"
"    }\n"
"    else if (!isActive) // directly remove the panel\n"
"    {\n"
"      this.DOMSearchBox().className = 'MSearchBoxInactive';\n"
"      this.DOMSearchField().value   = 'Search';\n"
"      this.searchActive             = false;\n"
"      this.lastSearchValue          = ''\n"
"      this.lastResultsPage          = '';\n"
"    }\n"
"  }\n"
"}\n"
"\n"
"// -----------------------------------------------------------------------\n"
"\n"
"// The class that handles everything on the search results page.\n"
"function SearchResults(name)\n"
"{\n"
"    // The number of matches from the last run of <Search()>.\n"
"    this.lastMatchCount = 0;\n"
"\n"
"    // Toggles the visibility of the passed element ID.\n"
"    this.Toggle = function(id)\n"
"    {\n"
"      var parentElement = document.getElementById(id);\n"
"      var element = parentElement.firstChild;\n"
"\n"
"      while (element && element!=parentElement)\n"
"      {\n"
"        if (element.nodeName == 'DIV' && element.className == 'SRChildren')\n"
"        {\n"
"          if (element.style.display == 'block')\n"
"          {  \n"
"            element.style.display = 'none';  \n"
"          }\n"
"          else\n"
"          {  \n"
"            element.style.display = 'block';  \n"
"          }\n"
"        }\n"
"\n"
"        if (element.nodeName == 'DIV' && element.hasChildNodes())\n"
"        {  \n"
"           element = element.firstChild;  \n"
"        }\n"
"        else if (element.nextSibling)\n"
"        {  \n"
"           element = element.nextSibling;  \n"
"        }\n"
"        else\n"
"        {\n"
"          do\n"
"          {\n"
"            element = element.parentNode;\n"
"          }\n"
"          while (element && element!=parentElement && !element.nextSibling);\n"
"\n"
"          if (element && element!=parentElement)\n"
"          {  \n"
"            element = element.nextSibling;  \n"
"          }\n"
"        }\n"
"      }\n"
"    }\n"
"\n"
"    // Searches for the passed string.  If there is no parameter, \n"
"    // it takes it from the URL query.\n"
"    //\n"
"    // Always returns true, since other documents may try to call it \n"
"    // and that may or may not be possible.\n"
"    this.Search = function(search)\n"
"    {\n"
"      if (!search) // get search word from URL\n"
"      {\n"
"        search = window.location.search;\n"
"        search = search.substring(1);  // Remove the leading '?'\n"
"        search = unescape(search);\n"
"      }\n"
"\n"
"      search = search.replace(/^ +/, \"\"); // strip leading spaces\n"
"      search = search.replace(/ +$/, \"\"); // strip trailing spaces\n"
"      search = search.toLowerCase();\n"
"      search = convertToId(search);\n"
"\n"
"      var resultRows = document.getElementsByTagName(\"div\");\n"
"      var matches = 0;\n"
"\n"
"      var i = 0;\n"
"      while (i < resultRows.length)\n"
"      {\n"
"        var row = resultRows.item(i);\n"
"        if (row.className == \"SRResult\")\n"
"        {\n"
"          var rowMatchName = row.id.toLowerCase();\n"
"          rowMatchName = rowMatchName.replace(/^sr\\d*_/, ''); // strip 'sr123_'\n"
"\n"
"          if (search.length<=rowMatchName.length && \n"
"             rowMatchName.substr(0, search.length)==search)\n"
"          {\n"
"            row.style.display = \"block\";\n"
"            matches++;\n"
"          }\n"
"          else\n"
"          {  \n"
"            row.style.display = \"none\";  \n"
"          }\n"
"        }\n"
"        i++;\n"
"      }\n"
"      document.getElementById(\"Searching\").style.display=\"none\";\n"
"      if (matches == 0) // no results\n"
"      {  \n"
"        document.getElementById(\"NoMatches\").style.display=\"block\";  \n"
"      }\n"
"      else // at least one result\n"
"      {  \n"
"        document.getElementById(\"NoMatches\").style.display=\"none\";  \n"
"      }\n"
"      this.lastMatchCount = matches;\n"
"      return true;\n"
"    }\n"
"}\n"
