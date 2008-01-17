/******************************************************************************
 *
 * 
 *
 * Copyright (C) 1997-2008 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#ifndef TRANSLATOR_SR_H
#define TRANSLATOR_SR_H

// translation by Dejan D. M. Milosavljevic <dmilos@email.com>;<dmilosx@ptt.yu>;<office@ddmrm.com>
// // 10x 2 Ivana Miletic for gramatical consutation.

// UTF-8 patch by Nenad Bulatovic <buletina@gmail.com>

class TranslatorSerbian : public TranslatorAdapter_1_4_1
{                                
private:
   QCString decode(const QCString& sInput)
   { 
//#ifdef _WIN32
//     return ISO88592ToWin1250(sInput);
//#else
     return sInput;
//#endif
   }


  public:

    // --- Language control methods -------------------
    
    /*! Used for identification of the language. The identification 
     * should not be translated. It should be replaced by the name 
     * of the language in English using lower-case characters only
     * (e.g. "czech", "japanese", "russian", etc.). It should be equal to 
     * the identification used in language.cpp.
     */
    virtual QCString idLanguage()
    { return "serbian"; }
    
    /*! Used to get the LaTeX command(s) for the language support. 
     *  This method should return string with commands that switch
     *  LaTeX to the desired language.  For example 
     *  <pre>"\\usepackage[german]{babel}\n"
     *  </pre>
     *  or
     *  <pre>"\\usepackage{polski}\n"
     *  "\\usepackage[latin2]{inputenc}\n"
     *  "\\usepackage[T1]{fontenc}\n"
     *  </pre>
     * 
     * The English LaTeX does not use such commands.  Because of this
     * the empty string is returned in this implementation.
     */
    virtual QCString latexLanguageSupportCommand()
    {
      QCString result="\\usepackage[serbian]{babel}\n";
      return result;
    }

    /*! return the language charset. This will be used for the HTML output */
    virtual QCString idLanguageCharset()
    {
//#ifdef _WIN32
//        { return "windows-1250"; }
//#else
        { return "UTF-8"; }
//#endif
    }

    // --- Language translation methods -------------------

    /*! used in the compound documentation before a list of related functions. */
    virtual QCString trRelatedFunctions()
    { return decode( "Povezane funkcije" ); }  

    /*! subscript for the related functions. */
    virtual QCString trRelatedSubscript()
    { return decode( "(To nisu funkcije članice.)" ); } 

    /*! header that is put before the detailed description of files, classes and namespaces. */
    virtual QCString trDetailedDescription()
    { return decode( "Opširnije objašnjenje" ); } // detalj je francuska rec.

    /*! header that is put before the list of typedefs. */
    virtual QCString trMemberTypedefDocumentation()
    { return decode( "Dokumentacija typedef članova" ); }
    
    /*! header that is put before the list of enumerations. */
    virtual QCString trMemberEnumerationDocumentation()
    { return decode( "Dokumentacija enum članova" ); }
    
    /*! header that is put before the list of member functions. */
    virtual QCString trMemberFunctionDocumentation()
    { return decode( "Dokumentacija funkcija članica" ); }
    
    /*! header that is put before the list of member attributes. */
    virtual QCString trMemberDataDocumentation()
    { 
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return decode( "Dokumentacija članova" ); 
      }
      else
      {
        return decode( "Dokumentacija javnih članova" ); 
      }
    }

    /*! this is the text of a link put after brief descriptions. */
    virtual QCString trMore() 
    { return decode( "Još..." ); }

    /*! put in the class documentation */
    virtual QCString trListOfAllMembers()
    { return decode( "Spisak svih članova." ); }

    /*! used as the title of the "list of all members" page of a class */
    virtual QCString trMemberList()
    { return decode( "Spisak članova" ); }

    /*! this is the first part of a sentence that is followed by a class name */
    virtual QCString trThisIsTheListOfAllMembers()
    { return decode( "Ovo je spisak svih članova " ); }

    /*! this is the remainder of the sentence after the class name */
    virtual QCString trIncludingInheritedMembers()
    { return decode( ", uključujući nasleđene članove." ); }
    
    /*! this is put at the author sections at the bottom of man pages.
     *  parameter s is name of the project name.
     */
    virtual QCString trGeneratedAutomatically(const char *s)
    { QCString result="Napravljeno automatski Doxygen-om";
      if( s ) result+=(QCString)" za " + s;
      result+=" od izvornog koda."; 
      return decode( result );
    }

    /*! put after an enum name in the list of all members */
    virtual QCString trEnumName()
    { return decode( "ime enum-a " ); }
    
    /*! put after an enum value in the list of all members */
    virtual QCString trEnumValue()
    { return decode( "vrednost enum-a" ); }
    
    /*! put after an undocumented member in the list of all members */
    virtual QCString trDefinedIn()
    { return decode( "definisano u" ); }

    // quick reference sections

    /*! This is put above each page as a link to the list of all groups of 
     *  compounds or files (see the \\group command).
     */
    virtual QCString trModules()
    { return decode( "Moduli" ); }
    
    /*! This is put above each page as a link to the class hierarchy */
    virtual QCString trClassHierarchy()
    { return decode( "Stablo klasa" ); }
    
    /*! This is put above each page as a link to the list of annotated classes */
    virtual QCString trCompoundList()
    { 
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return decode( "Sve strukture" );
      }
      else
      {
        return decode( "Sve klase" ); 
      }
    }
    
    /*! This is put above each page as a link to the list of documented files */
    virtual QCString trFileList()
    { return decode( "Spisak datoteka" ); }

    /*! This is put above each page as a link to the list of all verbatim headers */
    virtual QCString trHeaderFiles()
    { return decode( "Zaglavlja" ); }

    /*! This is put above each page as a link to all members of compounds. */
    virtual QCString trCompoundMembers()
    { 
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return decode( "Svi članovi struktura" ); 
      }             
      else
      {
        return decode( "Svi članovi klasa" ); 
      }
    }

    /*! This is put above each page as a link to all members of files. */
    virtual QCString trFileMembers()
    { 
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
       return decode( "Članovi datoteke" ); 
      }
      else
      {
       return decode( "Članovi datoteke" ); 
      }
    }

    /*! This is put above each page as a link to all related pages. */
    virtual QCString trRelatedPages()
    { return decode( "Stranice povezane sa ovom" ); }

    /*! This is put above each page as a link to all examples. */
    virtual QCString trExamples()
    { return decode( "Primeri" ); }

    /*! This is put above each page as a link to the search engine. */
    virtual QCString trSearch()
    { return decode( "Traži" ); }

    /*! This is an introduction to the class hierarchy. */
    virtual QCString trClassHierarchyDescription()
    { return decode( "Stablo nasleđivanja je složeno "
                     "približno po abecedi:" ); }

    /*! This is an introduction to the list with all files. */
    virtual QCString trFileListDescription(bool extractAll)
    {
      QCString result="Spisak svih ";
      if (!extractAll) result+="dokumetovanih ";
      result+="datoteka, sa kratkim opisom:";
      return decode( result );
    }

    /*! This is an introduction to the annotated compound list. */
    virtual QCString trCompoundListDescription()
    { 
      
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return decode( "Spisak struktura sa kratkim opisom:" ); 
      }
      else
      {
        return decode( "Spisak klasa, struktura, unija i interfejsa sa kratkim opisom:" );
               
      }
    }

    /*! This is an introduction to the page with all class members. */
    virtual QCString trCompoundMembersDescription(bool extractAll)
    {
      QCString result="Spisak svih ";
      if (!extractAll)
      {
        result+="dokumentovanih ";
      }
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        result+="članova struktura ili unija";
      }
      else
      {
        result+="članova klasa";
      }
      result+=" sa linkovima na ";
      if (extractAll) 
      {
        if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
        {
          result+="dokumentaciju članova struktura/unija:";  
        }
        else
        {
          result+="dokumentaciju svakog člana klase:";       
        }
      }
      else 
      {
        if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
        {
          result+="strukture/unije koje pripadaju:";
        }
        else
        {
          result+="klase koje pripadaju:"; 
        }
      }
      return decode( result );
    }

    /*! This is an introduction to the page with all file members. */
    virtual QCString trFileMembersDescription(bool extractAll)
    {
      QCString result="Spisak svih ";
      if (!extractAll) result+="dokumentovanih ";
      
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        result+="funkcija, promenjiva, makro zamena, enum-ova, i typedef-ova";
      }
      else
      {
        result+="članova";               
      }
     
      result+=" sa linkovima na ";
      
      if (extractAll) 
        result+="datoteke u kojima se nalaze:";
      else 
        result+=" dokumentaciju:";

      return decode( result );
    }

    /*! This is an introduction to the page with the list of all header files. */
    virtual QCString trHeaderFilesDescription()
    { return decode( "Zaglavlja koje izgrađuju API:" ); }

    /*! This is an introduction to the page with the list of all examples */
    virtual QCString trExamplesDescription()
    { return decode( "Spisak primera:" ); }

    /*! This is an introduction to the page with the list of related pages */
    virtual QCString trRelatedPagesDescription()
    { return decode( "Spisak svih sličnih stranica:" ); }

    /*! This is an introduction to the page with the list of class/file groups */
    virtual QCString trModulesDescription()
    { return decode( "Spisak svih modula:" ); }

    /*! This sentences is used in the annotated class/file lists if no brief
     * description is given. 
     */
    virtual QCString trNoDescriptionAvailable()
    { return decode( "Opis nije dostupan" ); }
    
    // index titles (the project name is prepended for these) 


    /*! This is used in HTML as the title of index.html. */
    virtual QCString trDocumentation()
    { return decode("Dokumentacija" ); }

    /*! This is used in LaTeX as the title of the chapter with the 
     * index of all groups.
     */
    virtual QCString trModuleIndex()
    { return decode( "Index modula" ); }

    /*! This is used in LaTeX as the title of the chapter with the 
     * class hierarchy.
     */
    virtual QCString trHierarchicalIndex()
    { return decode( "Hijerarhijski sadžraj" ); }

    /*! This is used in LaTeX as the title of the chapter with the 
     * annotated compound index.
     */
    virtual QCString trCompoundIndex()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      { 
        return decode( "Glavni sadržaj" ); 
      }
      else
      {
        return decode( "Glavni sadržaj" ); 
      }
    }

    /*! This is used in LaTeX as the title of the chapter with the
     * list of all files.
     */
    virtual QCString trFileIndex() 
    { return decode( "Indeks datoteka" ); }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all groups.
     */
    virtual QCString trModuleDocumentation()
    { return decode( "Dokumentacija modula" ); }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all classes, structs and unions.
     */
    virtual QCString trClassDocumentation()
    { 
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Dokumentacija stuktura"; 
      }
      else
      {
        return "Dokumentacija klasa"; 
      }
    }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all files.
     */
    virtual QCString trFileDocumentation()
    { return "Dokumentacija datoteke"; }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all examples.
     */
    virtual QCString trExampleDocumentation()
    { return "Dokumentacija primera"; }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all related pages.
     */
    virtual QCString trPageDocumentation()
    { return "Dokumentacija stranice"; }

    /*! This is used in LaTeX as the title of the document */
    virtual QCString trReferenceManual()
    { return decode( "Priručnik" ); }
    
    /*! This is used in the documentation of a file as a header before the 
     *  list of defines
     */
    virtual QCString trDefines()
    { return "Makro zamene"; }

    /*! This is used in the documentation of a file as a header before the 
     *  list of function prototypes
     */
    virtual QCString trFuncProtos()
    { return "Deklaracija funkcije"; }

    /*! This is used in the documentation of a file as a header before the 
     *  list of typedefs
     */
    virtual QCString trTypedefs()
    { return "Typedef-ovi"; }

    /*! This is used in the documentation of a file as a header before the 
     *  list of enumerations
     */
    virtual QCString trEnumerations()
    { return "Enum-ovi"; }

    /*! This is used in the documentation of a file as a header before the 
     *  list of (global) functions
     */
    virtual QCString trFunctions()
    { return "Funkcije"; }

    /*! This is used in the documentation of a file as a header before the 
     *  list of (global) variables
     */
    virtual QCString trVariables()
    { return "Promenjive"; }

    /*! This is used in the documentation of a file as a header before the 
     *  list of (global) variables
     */
    virtual QCString trEnumerationValues()
    { return "Vrednosti enum-ova"; }
    
    /*! This is used in the documentation of a file before the list of
     *  documentation blocks for defines
     */
    virtual QCString trDefineDocumentation()
    { return "Dokumentacija makro zamene"; }

    /*! This is used in the documentation of a file/namespace before the list 
     *  of documentation blocks for function prototypes
     */
    virtual QCString trFunctionPrototypeDocumentation()
    { return "Dokumentacija deklaracije funkcije"; }

    /*! This is used in the documentation of a file/namespace before the list 
     *  of documentation blocks for typedefs
     */
    virtual QCString trTypedefDocumentation()
    { return "Dokumentacija typedef-a"; }

    /*! This is used in the documentation of a file/namespace before the list 
     *  of documentation blocks for enumeration types
     */
    virtual QCString trEnumerationTypeDocumentation()
    { return "Dokumetacija enum-a"; }

    /*! This is used in the documentation of a file/namespace before the list 
     *  of documentation blocks for enumeration values
     */
    virtual QCString trEnumerationValueDocumentation()
    { return "Dokumentacija enum vrednosti"; }

    /*! This is used in the documentation of a file/namespace before the list 
     *  of documentation blocks for functions
     */
    virtual QCString trFunctionDocumentation()
    { return "Dokumentacija funkcije"; }

    /*! This is used in the documentation of a file/namespace before the list 
     *  of documentation blocks for variables
     */
    virtual QCString trVariableDocumentation()
    { return "Dokumentacija promenjive"; }

    /*! This is used in the documentation of a file/namespace/group before 
     *  the list of links to documented compounds
     */
    virtual QCString trCompounds()
    { 
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Strukture";  
      }
      else
      {
        return "Klase i strukture";   
      }
    }

    /*! This is used in the standard footer of each page and indicates when 
     *  the page was generated 
     */
    virtual QCString trGeneratedAt(const char *date,const char *projName)
    { 
      QCString result=(QCString)"Napravljeno " + date;
      if ( projName ) result+=(QCString)" za " + projName;
      result+=(QCString)" od";
      return decode( result );
    }
    /*! This is part of the sentence used in the standard footer of each page.
     */
    virtual QCString trWrittenBy()
    {
      return "napisao";
    }

    /*! this text is put before a class diagram */
    virtual QCString trClassDiagram(const char *clName)
    {
      return decode( QCString("Dijagram nasleđivanja za klasu ") + clName + ":" );
    }
    
    /*! this text is generated when the \\internal command is used. */
    virtual QCString trForInternalUseOnly()
    { return decode( "Samo za unutrašnju upotrebu." ); }

    /*! this text is generated when the \\reimp command is used. */
    virtual QCString trReimplementedForInternalReasons()
    { return decode("Preurađeno zbog unutrašnjih razloga; Nema uticaja na API." ); }

    /*! this text is generated when the \\warning command is used. */
    virtual QCString trWarning()
    { return "Upozorenje"; }

    /*! this text is generated when the \\bug command is used. */
    virtual QCString trBugsAndLimitations()
    { return decode( "Greške i ograničenja" ); }

    /*! this text is generated when the \\version command is used. */
    virtual QCString trVersion()
    { return "Verzija"; }    // inacica

    /*! this text is generated when the \\date command is used. */
    virtual QCString trDate()
    { return "Datum"; }

    /*! this text is generated when the \\return command is used. */
    virtual QCString trReturns()
    { return decode( "Vraćene vrednosti" ); }

    /*! this text is generated when the \\sa command is used. */
    virtual QCString trSeeAlso()
    { return decode( "Takođe pogledati" ); }

    /*! this text is generated when the \\param command is used. */
    virtual QCString trParameters()
    { return "Parametri"; }

    /*! this text is generated when the \\exception command is used. */
    virtual QCString trExceptions()
    { return "Izuzeci"; }
    
    /*! this text is used in the title page of a LaTeX document. */
    virtual QCString trGeneratedBy()
    { return "Napravio"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990307
//////////////////////////////////////////////////////////////////////////
    
    /*! used as the title of page containing all the index of all namespaces. */
    virtual QCString trNamespaceList()
    { return "Spisak prostora imena"; }

    /*! used as an introduction to the namespace list */
    virtual QCString trNamespaceListDescription(bool extractAll)
    {
      QCString result="Spisak svih ";
      if (!extractAll) result+="dokumentovanih ";
      result+="prostora imena sa kratkim opisom:";
      return decode( result );
    }

    /*! used in the class documentation as a header before the list of all
     *  friends of a class
     */
    virtual QCString trFriends()
    { return "Prijatelji"; }
    
//////////////////////////////////////////////////////////////////////////
// new since 0.49-990405
//////////////////////////////////////////////////////////////////////////
    
    /*! used in the class documentation as a header before the list of all
     * related classes 
     */
    virtual QCString trRelatedFunctionDocumentation()
    { return decode( "Dokumentacija prijateljskih funkcija ili klasa" ); }
    
//////////////////////////////////////////////////////////////////////////
// new since 0.49-990425
//////////////////////////////////////////////////////////////////////////

    /*! used as the title of the HTML page of a class/struct/union */
    virtual QCString trCompoundReference(const char *clName,
                                    ClassDef::CompoundType compType,
                                    bool isTemplate)
    {                            
      QCString result( "Dokumentacija " );   
      
      switch(compType)
      {
        case ClassDef::Class:      result+="klase "; break;
        case ClassDef::Struct:     result+="strukture "; break;
        case ClassDef::Union:      result+="unije "; break;
        case ClassDef::Interface:  result+="interfejsa "; break;
        case ClassDef::Protocol:   result+="protokola "; break; // grcka rec
        case ClassDef::Category:   result+="kategorije "; break; // 
        case ClassDef::Exception:  result+="izuzetka "; break;
      }
      if (isTemplate) result += "šablona ";  
      
      result += clName;
      return decode( result );
    }

    /*! used as the title of the HTML page of a file */
    virtual QCString trFileReference(const char *fileName)
    {
      QCString result = "Opis datoteke ";
      result += fileName; 
      return decode( result );
    }

    /*! used as the title of the HTML page of a namespace */
    virtual QCString trNamespaceReference(const char *namespaceName)
    {
      QCString result="Opis prostora imena ";
      result += namespaceName;
      return result;
    }
    
    virtual QCString trPublicMembers()
    { return decode("Javni članovi"); }
    virtual QCString trPublicSlots()
    { return "Javni slotovi"; }
    virtual QCString trSignals()
    { return "Signali"; }
    virtual QCString trStaticPublicMembers()
    { return decode("Zajednički javni članovi"); }
    virtual QCString trProtectedMembers()
    { return decode("Zaštićeni članovi");  }
    virtual QCString trProtectedSlots()
    { return decode("Zaštićeni slotovi"); }
    virtual QCString trStaticProtectedMembers()
    { return decode("Zajednički zaštićeni članovi"); }
    virtual QCString trPrivateMembers()
    { return decode("Privatni članovi"); }
    virtual QCString trPrivateSlots()
    { return decode("Privatni slotovi"); }
    virtual QCString trStaticPrivateMembers()
    { return decode("Zajednički privatni članovi"); }
    
    /*! this function is used to produce a comma-separated list of items.
     *  use generateMarker(i) to indicate where item i should be put.
     */
    virtual QCString trWriteList(int numEntries)
    {
      QCString result;
      int i;
      // the inherits list contain `numEntries' classes
      for (i=0;i<numEntries;i++) 
      {
        // use generateMarker to generate placeholders for the class links!
        result+=generateMarker(i); // generate marker for entry i in the list 
                                   // (order is left to right)
        
        if (i!=numEntries-1)  // not the last entry, so we need a separator
        {
          if (i<numEntries-2) // not the fore last entry 
            result+=", ";
          else                // the fore last entry
            result+=" i ";
        }
      }
      return result; 
    }
    
    /*! used in class documentation to produce a list of base classes,
     *  if class diagrams are disabled.
     */
    virtual QCString trInheritsList(int numEntries)
    {
      return decode("Nasleđeno od "+trWriteList(numEntries)+".");
    }

    /*! used in class documentation to produce a list of super classes,
     *  if class diagrams are disabled.
     */
    virtual QCString trInheritedByList(int numEntries)
    {
      return decode( "Nasleđeno u "+trWriteList(numEntries)+"." );
    }

    /*! used in member documentation blocks to produce a list of 
     *  members that are hidden by this one.
     */
    virtual QCString trReimplementedFromList(int numEntries)
    {
      return decode("Preurađeno od "+trWriteList(numEntries)+"." );
    }

    /*! used in member documentation blocks to produce a list of
     *  all member that overwrite the implementation of this member.
     */
    virtual QCString trReimplementedInList(int numEntries)
    {
      return decode("Preurađeno u "+trWriteList(numEntries)+"." );
    }

    /*! This is put above each page as a link to all members of namespaces. */
    virtual QCString trNamespaceMembers()
    { return decode("Članovi prostora imena"); }

    /*! This is an introduction to the page with all namespace members */
    virtual QCString trNamespaceMemberDescription(bool extractAll)
    { 
      QCString result="Spisak svih ";
      if (!extractAll) result+="dokumentovanih ";
      result+="članova prostora imena sa linkovima na ";
      if (extractAll) 
        result+="dokumentaciju svakog člana prostora imena: ";
      else 
        result+="prostor imena kojima pripadaju: ";
      return decode( result );
    }
    /*! This is used in LaTeX as the title of the chapter with the 
     *  index of all namespaces.
     */
    virtual QCString trNamespaceIndex()
    { return "Index prostora imena"; }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all namespaces.
     */
    virtual QCString trNamespaceDocumentation()
    { return "Dokumentacija prostora imena"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990522
//////////////////////////////////////////////////////////////////////////

    /*! This is used in the documentation before the list of all
     *  namespaces in a file.
     */
    virtual QCString trNamespaces()
    { return "Prostori imena"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990728
//////////////////////////////////////////////////////////////////////////

    /*! This is put at the bottom of a class documentation page and is
     *  followed by a list of files that were used to generate the page.
     */
    virtual QCString trGeneratedFromFiles(ClassDef::CompoundType compType,
        bool single)
    { // here s is one of " Class", " Struct" or " Union"
      // single is true implies a single file
      QCString result=(QCString)"Dokumentacija ";
      switch(compType)
      {
        case ClassDef::Class:      result+="ove klase"; break;
        case ClassDef::Struct:     result+="ove strukture"; break;
        case ClassDef::Union:      result+="ove unije"; break;
        case ClassDef::Interface:  result+="ovog interfejsa"; break;
        case ClassDef::Protocol:   result+="ovog protokola"; break;
        case ClassDef::Category:   result+="ove kategorije"; break;
        case ClassDef::Exception:  result+="ovog izuzetka"; break;
      }
      result+=" je napravljena iz ";
      if (single) result+=":"; else result+=":";
      return result;
    }

    /*! This is in the (quick) index as a link to the alphabetical compound
     * list.
     */
    virtual QCString trAlphabeticalList()
    { return "Abecedni spisak"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990901
//////////////////////////////////////////////////////////////////////////

    /*! This is used as the heading text for the retval command. */
    virtual QCString trReturnValues()
    { return decode( "Vraćena vrednost" ); }

    /*! This is in the (quick) index as a link to the main page (index.html)
     */
    virtual QCString trMainPage()
    { return "Glavna strana"; }

    /*! This is used in references to page that are put in the LaTeX 
     *  documentation. It should be an abbreviation of the word page.
     */
    virtual QCString trPageAbbreviation()
    { return "str."; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-991003
//////////////////////////////////////////////////////////////////////////

    virtual QCString trSources()
    {
      return "Izvorne datoteke";
    }
    virtual QCString trDefinedAtLineInSourceFile()
    {
      return "Definisano u redu @0 datoteke @1.";
    }
    virtual QCString trDefinedInSourceFile()
    {
      return "Definisano u datoteci @0.";
    }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-991205
//////////////////////////////////////////////////////////////////////////

    virtual QCString trDeprecated()
    {
      return "Zastarelo";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.0.0
//////////////////////////////////////////////////////////////////////////

    /*! this text is put before a collaboration diagram */
    virtual QCString trCollaborationDiagram(const char *clName)
    {
      return decode( (QCString)"Dijagram nasleđenih članova za "+clName+":" );
    }
    /*! this text is put before an include dependency graph */
    virtual QCString trInclDepGraph(const char *fName)
    {
      return decode( (QCString)"Graf zavisnosti datoteka za "+fName+":" );
    }
    /*! header that is put before the list of constructor/destructors. */
    virtual QCString trConstructorDocumentation()
    {
      return "Dokumentacija konstruktora i destruktora"; 
    }
    /*! Used in the file documentation to point to the corresponding sources. */
    virtual QCString trGotoSourceCode()
    {
      return "Izvorni kod.";
    }
    /*! Used in the file sources to point to the corresponding documentation. */
    virtual QCString trGotoDocumentation()
    {
      return "Dokumentacija.";
    }
    /*! Text for the \\pre command */
    virtual QCString trPrecondition()
    {
      return "Preduslovi";
    }
    /*! Text for the \\post command */
    virtual QCString trPostcondition()
    {
      return "Postuslovi";
    }
    /*! Text for the \\invariant command */
    virtual QCString trInvariant()
    {
      return "Invarijanta";
    }
    /*! Text shown before a multi-line variable/enum initialization */
    virtual QCString trInitialValue()
    {
      return decode( "Početna vrednost:" );
    }
    /*! Text used the source code in the file index */
    virtual QCString trCode()
    {
      return "kod";
    }
    virtual QCString trGraphicalHierarchy()
    {
      return decode("Grafički prikaz stabla klasa");
    }
    virtual QCString trGotoGraphicalHierarchy()
    {
      return decode("Prikaži stablo klasa u grafičkom obliku");
    }
    virtual QCString trGotoTextualHierarchy()
    {
      return decode( "Prikaži stablo klasa u tekstualnom obliku" );
    }
    virtual QCString trPageIndex()
    {
      return "Indeks stranice";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.1.0
//////////////////////////////////////////////////////////////////////////
    
    virtual QCString trNote()
    {
      return "Primedba"; // ili Beleska ili Zapazanje. Primedba zvuci negativno
    }
    virtual QCString trPublicTypes()
    {
      return "Javni tipovi";
    }
    virtual QCString trPublicAttribs()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return decode( "Članovi" );        
      }
      else
      {
        return decode( "Javni članovi" );
      }
    }
    virtual QCString trStaticPublicAttribs()
    {
      return decode( "Zajednički javni članovi");
    }
    virtual QCString trProtectedTypes()
    {
      return decode( "Zaštićeni tipovi" );
    }
    virtual QCString trProtectedAttribs()
    {
      return decode( "Zaštićeni članovi" );
    }
    virtual QCString trStaticProtectedAttribs()
    {
      return decode( "Zajednički zaštićeni članovi" );
    }
    virtual QCString trPrivateTypes()
    {
      return decode( "Privatni tipovi" );
    }
    virtual QCString trPrivateAttribs()
    {
      return decode( "Privatni članovi" );
    }
    virtual QCString trStaticPrivateAttribs()
    {
      return decode( "Zajednički privatni članovi" );
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.1.3
//////////////////////////////////////////////////////////////////////////

    /*! Used as a marker that is put before a \\todo item */
    virtual QCString trTodo()
    {
      return decode( "Neurađeno" );
    }
    /*! Used as the header of the todo list */
    virtual QCString trTodoList()
    {
      return decode("Spisak neurađenog");
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.1.4
//////////////////////////////////////////////////////////////////////////

    virtual QCString trReferencedBy()
    {
      return decode( "Korišćeno od" ); 
    }
    virtual QCString trRemarks()
    {
      return decode( "Zapažanja" );
    }
    virtual QCString trAttention()
    {
      return decode( "Pažnja" );
    }
    virtual QCString trInclByDepGraph()
    {
      return decode("Ovaj graf pokazuje koja datoteka direktno "
      "ili indirektno uključuju ovu datoteku: ");
    }
    virtual QCString trSince()
    {
      return "Od";
    }
    
//////////////////////////////////////////////////////////////////////////
// new since 1.1.5
//////////////////////////////////////////////////////////////////////////

    /*! title of the graph legend page */
    virtual QCString trLegendTitle()
    {
      return decode( "Objašnjenje korišćenih simbola" );
    }
    /*! page explaining how the dot graph's should be interpreted 
     *  The %A in the text below are to prevent link to classes called "A".
     */
    virtual QCString trLegendDocs()
    {
      return decode(        
       "Ova stranica objašnjava kako tumačiti grafikone koje je napravio "
        "doxygen.<p>\n"
        "Na primer:\n"
        "\\code\n"
        "/*! Nevidljiva klasa ( nemo�e stati na graf zbog zadatih ograni�enja ) */\n"
        "class Invisible { };\n\n"
        "/*! Odse�ena klasa, neke osnovne klase su sakrivene */\n"
        "class Truncated : public Invisible { };\n\n"
        "/* Nedokumentovana klasa */\n"
        "class Undocumented { };\n\n"
        "/*! Javno nasle�ena klasa */\n"
        "class PublicBase : public Truncated { };\n\n"
        "/*! Sablon klasa */\n"
        "template<class T> class Templ { };\n\n"
        "/*! Za�ti�eno nasle�ena klasa */\n"
        "class ProtectedBase { };\n\n"
        "/*! Privatno nasle�ena klasa */\n"
        "class PrivateBase { };\n\n"
        "/*! Klasa koja je kori��ena od drugih klasa*/\n"
        "class Used { };\n\n"
        "/*! Nadklasa koja nasle�uje/koristi ostale */\n"
        "class Inherited : public PublicBase,\n"
        "                  protected ProtectedBase,\n"
        "                  private PrivateBase,\n"
        "                  public Undocumented,\n"
        "                  public Templ<int>\n"
        "{\n"
        "  private:\n"
        "    Used *m_usedClass;\n"
        "};\n"
        "\\endcode\n"
        "Ako je \\c MAX_DOT_GRAPH_HEIGHT tag u konfiguracionoj datoteci "
        "postavljen na  200 gornje veze će izgledati:"
        "<p><center><img src=\"graph_legend."+Config_getEnum("DOT_IMAGE_FORMAT")+"\"></center>\n"
        "<p>\n"
        
        "Pravougaonici imaju sledeća značenja:\n"
        "<ul>\n"
         "<li>Puni crni predstavlja strukturu ili klasu za koju je graf napravljen.\n"
         "<li>Sa crnom ivicom predstavlja dokumentovanu strukturu ili klasu.\n"
         "<li>Sa sivom ivicom predstavlja nedokumentovanu strukturu ili klasu.\n"
         "<li>Sa crvenom ivicom predstavlja dokumentovanu strukturu ili klasu\n"
         "za koju nije prikazan graf nasleđivanja/korišćenja. Graf je odsečen "
         "ako ne stane unutar određenih granica." 
        "</ul>" 
        "Strelice imaju sledeća značenja:\n"
        "<ul>\n"
         "<li>Tamnoplava strelica označava javno nasleđivanje.\n"
         "<li>Tamnozelena strelica označava zaštićeno nasleđivanje.\n"
         "<li>Tamnocrvena strelica označava privatno nasleđivanje.\n"
         "<li>Ljubičasta isprekidana strelica ako je klasa koristi ili je njen član. "
          "Strelica je označena imenom člana.\n"
         "<li>Zuta strelica označava vezu između primerka šablona"
          " i šablon klase od koje je napravljena. "
          "Strelica je označena imenom parametra šablona.\n"
        "</ul>\n"
         );

    }
    /*! text for the link to the legend page */
    virtual QCString trLegend()
    {
      return decode( "Objašnjenje korišćenih simbola" );
    }
    
//////////////////////////////////////////////////////////////////////////
// new since 1.2.0
//////////////////////////////////////////////////////////////////////////
    
    /*! Used as a marker that is put before a test item */
    virtual QCString trTest()
    {
      return "Test";
    }
    /*! Used as the header of the test list */
    virtual QCString trTestList()
    {
      return "Spisak testova";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.1
//////////////////////////////////////////////////////////////////////////

    /*! Used as a section header for KDE-2 IDL methods */
    virtual QCString trDCOPMethods()
    {
      return "DCOP metode";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.2
//////////////////////////////////////////////////////////////////////////

    /*! Used as a section header for IDL properties */
    virtual QCString trProperties()
    {
      return decode( "Osobine" );
    }
    /*! Used as a section header for IDL property documentation */
    virtual QCString trPropertyDocumentation()
    {
      return decode( "Dokumentacija osobina" );
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.4
//////////////////////////////////////////////////////////////////////////

    /*! Used for Java interfaces in the summary section of Java packages */
    virtual QCString trInterfaces()
    {
      return "Interfejsi";  // Radna okruzenja. Ali to je dve reci.
    }
    /*! Used for Java classes in the summary section of Java packages */
    virtual QCString trClasses()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Strukture";
      }
      else
      {
        return "Klase";
      }
    }
    /*! Used as the title of a Java package */
    virtual QCString trPackage(const char *name)
    {
      return (QCString)"Paket "+name;
    }
    /*! Title of the package index page */
    virtual QCString trPackageList()
    {
      return "Spisak paketa";
    }
    /*! The description of the package index page */
    virtual QCString trPackageListDescription()
    {
      return "Paketi s kratkim opisom (ukoliko postoji):";
    }
    /*! The link name in the Quick links header for each page */
    virtual QCString trPackages()
    {
      return "Paketi";
    }
    /*! Used as a chapter title for Latex & RTF output */
    virtual QCString trPackageDocumentation()
    {
      return "Dokumentacija paketa";
    }
    /*! Text shown before a multi-line define */
    virtual QCString trDefineValue()
    {
      return "Vrednost:";
    }
    
//////////////////////////////////////////////////////////////////////////
// new since 1.2.5
//////////////////////////////////////////////////////////////////////////
    
    /*! Used as a marker that is put before a \\bug item */
    virtual QCString trBug()
    {
      return decode( "Greška" );
    }
    /*! Used as the header of the bug list */
    virtual QCString trBugList()
    {
      return decode( "Spisak grešaka" );
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.6
//////////////////////////////////////////////////////////////////////////

    /*! Used as ansicpg for RTF file 
     * 
     * The following table shows the correlation of Charset name, Charset Value and 
     * <pre>
     * Codepage number:
     * Charset Name       Charset Value(hex)  Codepage number
     * ------------------------------------------------------
     * DEFAULT_CHARSET           1 (x01)
     * SYMBOL_CHARSET            2 (x02)
     * OEM_CHARSET             255 (xFF)
     * ANSI_CHARSET              0 (x00)            1252
     * RUSSIAN_CHARSET         204 (xCC)            1251
     * EE_CHARSET              238 (xEE)            1250
     * GREEK_CHARSET           161 (xA1)            1253
     * TURKISH_CHARSET         162 (xA2)            1254
     * BALTIC_CHARSET          186 (xBA)            1257
     * HEBREW_CHARSET          177 (xB1)            1255
     * ARABIC _CHARSET         178 (xB2)            1256
     * SHIFTJIS_CHARSET        128 (x80)             932
     * HANGEUL_CHARSET         129 (x81)             949
     * GB2313_CHARSET          134 (x86)             936
     * CHINESEBIG5_CHARSET     136 (x88)             950
     * </pre>
     * 
     */
    virtual QCString trRTFansicp()
    {
      return "1252";
    }
    

    /*! Used as ansicpg for RTF fcharset 
     *  \see trRTFansicp() for a table of possible values.
     */
    virtual QCString trRTFCharSet()
    {
      return "238";
    }

    /*! Used as header RTF general index */
    virtual QCString trRTFGeneralIndex()
    {
      return decode( "Sadržaj" );
    }
   
    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names 
     *  of the category.
     */
    virtual QCString trClass(bool first_capital, bool singular)
    { 
      QCString result( (first_capital ? "Klas" : "klas") );
      result+= (singular ? "a" : "e");
      return result; 
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names 
     *  of the category.
     */
    virtual QCString trFile(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Datotek" : "Datotek"));
      result+= (singular ? "a" : "e");
      return result; 
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names 
     *  of the category.
     */
    virtual QCString trNamespace(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Prostor" : "prostor"));
      result += (singular ? "" : "i");
      result += " imena";
      return result; 
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names 
     *  of the category.
     */
    virtual QCString trGroup(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Grup" : "grup"));
      result+= (singular ? "a" : "e");
      return result; 
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names 
     *  of the category.
     */
    virtual QCString trPage(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Stran" : "stran"));
      result+= (singular ? "a" : "e");
      return result; 
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names 
     *  of the category.
     */
    virtual QCString trMember(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Član" : "član"));
      result+= (singular ? "" : "ovi");
      return decode( result ); 
    }
   
    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names 
     *  of the category.
     */
    virtual QCString trField(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Polj" : "polj"));
      result+= (singular ? "e" : "a");
      return result; 
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names 
     *  of the category.
     */
    virtual QCString trGlobal(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Global" : "global"));
      result+= (singular ? "no" : "ni");
      return result; 
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.7
//////////////////////////////////////////////////////////////////////////

    /*! This text is generated when the \\author command is used and
     *  for the author section in man pages. */
    virtual QCString trAuthor(bool first_capital, bool singular)
    {                                                                         
      QCString result((first_capital ? "Autor" : "autor"));
      result+= (singular ? "" : "i");
      return decode( result ); 
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.11
//////////////////////////////////////////////////////////////////////////

    /*! This text is put before the list of members referenced by a member
     */
    virtual QCString trReferences()
    {
      return decode( "Koristi" );
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.13
//////////////////////////////////////////////////////////////////////////

    /*! used in member documentation blocks to produce a list of 
     *  members that are implemented by this one.
     */
    virtual QCString trImplementedFromList(int numEntries)
    {
      return decode( "Definiše "+trWriteList(numEntries)+"." );
    }

    /*! used in member documentation blocks to produce a list of
     *  all members that implement this abstract member.
     */
    virtual QCString trImplementedInList(int numEntries)
    {
      return decode( "Definisano u " + trWriteList(numEntries) + "." );
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.16
//////////////////////////////////////////////////////////////////////////

    /*! used in RTF documentation as a heading for the Table
    *  of Contents.
         */
    virtual QCString trRTFTableOfContents()
     {
      return decode( "Sadržaj" );
     }
     
//////////////////////////////////////////////////////////////////////////
// new since 1.2.17
//////////////////////////////////////////////////////////////////////////

    /*! Used as the header of the list of item that have been 
     *  flagged deprecated 
     */
    virtual QCString trDeprecatedList()
    {
      return decode( "Spisak zastarelih funkcija članica" );
    } 
//////////////////////////////////////////////////////////////////////////
// new since 1.2.18
//////////////////////////////////////////////////////////////////////////

    /*! Used as a header for declaration section of the events found in 
     * a C# program
     */
    virtual QCString trEvents()
    {
      return decode( "Događaji" );
    }
    /*! Header used for the documentation section of a class' events. */
    virtual QCString trEventDocumentation()
    {
      return decode( "Dokumentacija događaja" );
    }
//////////////////////////////////////////////////////////////////////////
// new since 1.3
//////////////////////////////////////////////////////////////////////////

    /*! Used as a heading for a list of Java class types with package scope.
     */
    virtual QCString trPackageTypes()
    { 
      return decode( "Tipovi u Paketu" );
    }
    /*! Used as a heading for a list of Java class functions with package 
     * scope. 
     */
    virtual QCString trPackageMembers()
    { 
      return decode( "Funkcije u paketu" );
    }
    /*! Used as a heading for a list of static Java class functions with 
     *  package scope.
     */
    virtual QCString trStaticPackageMembers()
    { 
      return decode( "Statičke funkcije u paketu" );  // Zajednicke funkcije u paketu
    }
    /*! Used as a heading for a list of Java class variables with package 
     * scope.
     */
    virtual QCString trPackageAttribs()
    { 
      return decode( "Atributi u paketu" ); // Clanovi u paketu
    }
    /*! Used as a heading for a list of static Java class variables with 
     * package scope.
     */
    virtual QCString trStaticPackageAttribs()
    { 
      return decode( "Statički atributi u paketu" );  // Zajednicki clanovi u paketu
    }
    
//////////////////////////////////////////////////////////////////////////
// new since 1.3.1
//////////////////////////////////////////////////////////////////////////

    /*! Used in the quick index of a class/file/namespace member list page 
     *  to link to the unfiltered list of all members.
     */
    virtual QCString trAll()
    {
      return decode( "Sve" );
    }
    /*! Put in front of the call graph for a function. */
    virtual QCString trCallGraph()
    {
      return decode( "Graf pozivanja funkcija:" );
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.3.3
//////////////////////////////////////////////////////////////////////////

    /*! When the search engine is enabled this text is put in the header 
     *  of each page before the field where one can enter the text to search 
     *  for. 
     */
    virtual QCString trSearchForIndex()
    {
      return decode("Traži");
    }
    /*! This string is used as the title for the page listing the search
     *  results.
     */
    virtual QCString trSearchResultsTitle()
    {
      return decode( "Rezultati pretraživanja" );
    }
    /*! This string is put just before listing the search results. The
     *  text can be different depending on the number of documents found.
     *  Inside the text you can put the special marker $num to insert
     *  the number representing the actual number of search results.
     *  The @a numDocuments parameter can be either 0, 1 or 2, where the 
     *  value 2 represents 2 or more matches. HTML markup is allowed inside
     *  the returned string.
     */
    virtual QCString trSearchResults(int numDocuments)
    {
      if (numDocuments==0)
      {
        return decode("Nema dokumenta koji odgovaraju vašem upitu");
      }
      else if (numDocuments==1)
      { // 10x 2 Ivana Miletic 4 gramatical consutation.
        return decode("Nađen je <b>1</b> dokument koji odgovara vašem upitu.");
      }
    else if (numDocuments<5) 
    {  // 10x 2 Ivana Miletic 4 gramatical consutation.
      return decode("Nađena su <b>$num</b> dokumenta koji odgovaraju vašem upitu."
                    "Najbolji su prikazani prvi.");
    }
    else 
    {  // 10x 2 Ivana Miletic 4 gramatical consutation.
      return decode("Nađeno je <b>$num</b> dokumenata koji odgovaraju vašem upitu."
        "Najbolji su prikazani prvi.");
    }
    }
    /*! This string is put before the list of matched words, for each search 
     *  result. What follows is the list of words that matched the query.
     */
    virtual QCString trSearchMatches()
    {
      return decode( "Pronađeno:" );
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.3.8
//////////////////////////////////////////////////////////////////////////

    /*! This is used in HTML as the title of page with source code for file filename
     */
    virtual QCString trSourceFile(QCString& filename)
    {
      return decode( "Izvorni kod datoteke " + filename ) ;
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.3.9
//////////////////////////////////////////////////////////////////////////

    /*! This is used as the name of the chapter containing the directory
     *  hierarchy.
     */
    virtual QCString trDirIndex()
    { return decode( "Stablo direktorijuma" ); }

    /*! This is used as the name of the chapter containing the documentation
     *  of the directories.
     */
    virtual QCString trDirDocumentation()
    { return decode( "Dokumentacija direktorijuma" ); }

    /*! This is used as the title of the directory index and also in the
     *  Quick links of a HTML page, to link to the directory hierarchy.
     */
    virtual QCString trDirectories()
    { return decode( "direktorijumi" ); }

    /*! This returns a sentences that introduces the directory hierarchy. 
     *  and the fact that it is sorted alphabetically per level
     */
    virtual QCString trDirDescription()
    { return decode( "Stablo direktorijuma slozeno približno po abecednom redu" );
    }

    /*! This returns the title of a directory page. The name of the
     *  directory is passed via \a dirName.
     */
    virtual QCString trDirReference(const char *dirName)
    { QCString result=dirName; result+="Opis direktorijuma"; return decode( result ); }

    /*! This returns the word directory with or without starting capital
     *  (\a first_capital) and in sigular or plural form (\a singular).
     */
    virtual QCString trDir(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Direktorijum" : "direktorijum"));
      if (!singular) result+="i"; 
      return decode( result ); 
    }

 
};

// sh -    � - shashavo  (,�)
// dj -    � - djordje
// ch - �, � - chasha
// cc -    � - cciccifu
// zz -    � - zzaba     

#endif
