/******************************************************************************
 * Copyright (C) 1997-2007 by Dimitri van Heesch.
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
 * Brazilian Portuguese version by
 *   Fabio "FJTC" Jun Takada Chino <jun-chino at uol.com.br>
 *   Version: 1.4.6 (2006/06/26)
 *
 * History:
 *	 1.4.6
 *		- trCallerGraph() added.
 *      - trEnumerationValueDocumentation() added.
 *   1.4.1
 *		- Method trOverloadText() added.
 * 	 1.3.9
 *		- Updated to Doxygen 1.3.9
 * 	 1.3.8
 *		- Updated to Doxygen 1.3.8
 *   1.3.3:
 *      - Updated to Doxygen 1.3.3
 *   1.3.2:
 *      - Updated to Doxygen 1.3.2
 *   1.3:
 *      - Updated to Doxygen 1.3.x.
 *   1.2.19:
 *      - Updated to Doxygen 1.2.19
 *      - Translation Review (Thanks to Jorge Ramos and others)
 *      - Small fixes in C output.
 *      - Latex generation support fixed (invalid package name).
 */
#ifndef TRANSLATOR_BR_H
#define TRANSLATOR_BR_H

class TranslatorBrazilian : public Translator
{
  public:

    // --- Language control methods -------------------

    /*! Used for identification of the language. May resemble
     * the string returned by latexBabelPackage(), but it is not used
     * for the same purpose. The identification should not be translated.
     * It should be replaced by the name of the language in English
     * (e.g. Czech, Japanese, Russian, etc.). It should be equal to
     * the identification in language.h.
     */
    virtual QCString idLanguage()
    {
      return "brazil";
    }

    /*! Used to get the command(s) for the language support. This method
     *  was designed for languages which do not prefer babel package.
     *  If this methods returns empty string, then the latexBabelPackage()
     *  method is used to generate the command for using the babel package.
     */
    virtual QCString latexLanguageSupportCommand()
    {
      return "\\usepackage[spanish]{babel}";
    }

    /*! return the language charset. This will be used for the HTML output */
    virtual QCString idLanguageCharset()
    {
      return "iso-8859-1";
    }

    // --- Language translation methods -------------------

    /*! used in the compound documentation before a list of related functions. */
    virtual QCString trRelatedFunctions()
    { return "Fun��es Relacionadas"; }

    /*! subscript for the related functions. */
    virtual QCString trRelatedSubscript()
    { return "(Note que estas n�o s�o fun��es membros.)"; }

    /*! header that is put before the detailed description of files, classes and namespaces. */
    virtual QCString trDetailedDescription()
    { return "Descri��o Detalhada"; }

    /*! header that is put before the list of typedefs. */
    virtual QCString trMemberTypedefDocumentation()
    { return "Defini��es de Tipos"; }

    /*! header that is put before the list of enumerations. */
    virtual QCString trMemberEnumerationDocumentation()
    { return "Enumera��es"; }

    /*! header that is put before the list of member functions. */
    virtual QCString trMemberFunctionDocumentation()
    { return "M�todos"; }

    /*! header that is put before the list of member attributes. */
    virtual QCString trMemberDataDocumentation()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Campos e Atributos";
      }
      else
      {
        return "Constantes";
      }
    }

    /*! this is the text of a link put after brief descriptions. */
    virtual QCString trMore()
    { return "Mais..."; }

    /*! put in the class documentation */
    virtual QCString trListOfAllMembers()
    { return "Lista de todos os Membros."; }

    /*! used as the title of the "list of all members" page of a class */
    virtual QCString trMemberList()
    { return "Lista dos Membros"; }

    /*! this is the first part of a sentence that is followed by a class name */
    virtual QCString trThisIsTheListOfAllMembers()
    { return "Esta � a lista de todos os membros de "; }

    /*! this is the remainder of the sentence after the class name */
    virtual QCString trIncludingInheritedMembers()
    { return ", incluindo os membros herdados."; }

    /*! this is put at the author sections at the bottom of man pages.
     *  parameter s is name of the project name.
     */
    virtual QCString trGeneratedAutomatically(const char *s)
    { QCString result="Gerado automaticamente por Doxygen";
      if (s) result+=(QCString)" para "+s;
      result+=" a partir de seu c�digo-fonte.";
      return result;
    }

    /*! put after an enum name in the list of all members */
    virtual QCString trEnumName()
    { return "Nome da enumera��o"; }

    /*! put after an enum value in the list of all members */
    virtual QCString trEnumValue()
    { return "Valor enumerado"; }

    /*! put after an undocumented member in the list of all members */
    virtual QCString trDefinedIn()
    { return "definido(a) em"; }

    // quick reference sections

    /*! This is put above each page as a link to the list of all groups of
     *  compounds or files (see the \\group command).
     */
    virtual QCString trModules()
    { return "M�dulos"; }

    /*! This is put above each page as a link to the class hierarchy */
    virtual QCString trClassHierarchy()
    { return "Hierarquia de Classes"; }

    /*! This is put above each page as a link to the list of annotated classes */
    virtual QCString trCompoundList()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Estruturas de Dados";
      }
      else
      {
        return "Lista de Componentes";
      }
    }

    /*! This is put above each page as a link to the list of documented files */
    virtual QCString trFileList()
    { return "Lista de Arquivos"; }

    /*! This is put above each page as a link to all members of compounds. */
    virtual QCString trCompoundMembers()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Campos de Dados";
      }
      else
      {
        return "Componentes Membros";
      }
    }

    /*! This is put above each page as a link to all members of files. */
    virtual QCString trFileMembers()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Globais";
      }
      else
      {
        return "Arquivos Membros";
      }
    }

    /*! This is put above each page as a link to all related pages. */
    virtual QCString trRelatedPages()
    { return "P�ginas relacionadas"; }

    /*! This is put above each page as a link to all examples. */
    virtual QCString trExamples()
    { return "Exemplos"; }

    /*! This is put above each page as a link to the search engine. */
    virtual QCString trSearch()
    { return "Busca"; }

    /*! This is an introduction to the class hierarchy. */
    virtual QCString trClassHierarchyDescription()
    { return "Esta lista de hierarquias est� parcialmente ordenada (ordem alfab�tica):"; }

    /*! This is an introduction to the list with all files. */
    virtual QCString trFileListDescription(bool extractAll)
    {
      QCString result="Esta � a lista de todos os arquivos ";
      if (!extractAll) result+="documentados ";
      result+="e suas respectivas descri��es:";
      return result;
    }

    /*! This is an introduction to the annotated compound list. */
    virtual QCString trCompoundListDescription()
    {

      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Aqui est�o as estruturas de dados e suas respectivas descri��es:";
      }
      else
      {
        return "Aqui est�o as classes, estruturas, uni�es e interfaces e suas respectivas descri��es:";
      }
    }

    /*! This is an introduction to the page with all class members. */
    virtual QCString trCompoundMembersDescription(bool extractAll)
    {
      QCString result="Esta � a lista de ";
      
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        result+="todas as estruturas e campos de uni�es ";
        if (!extractAll)
        {
          result+="documentas";
        }
      }
      else
      {
        result+="todos os membros de classes ";
        if (!extractAll)
        {
          result+="documentos";
        }
      }
      result+=" com refer�ncias para ";
      if (!extractAll)
      {
        if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
        {
          result+="a documenta��o da estrutura/uni�o de cada campo:";
        }
        else
        {
          result+="a documenta��o da classe de cada membro:";
        }
      }
      else
      {
        if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
        {
          result+="a estrutura/uni�o a que pertencem:";
        }
        else
        {
          result+="a classe a que pertencem:";
        }
      }
      return result;
    }

    /*! This is an introduction to the page with all file members. */
    virtual QCString trFileMembersDescription(bool extractAll)
    {
      QCString result="Esta � a lista de ";
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        result+="todas as fun��es, vari�veis, defini��es, enumera��es e defini��es de tipos ";
        if (!extractAll) result+="documentadas ";
      }
      else
      {
        result+="todos os membros dos arquivos ";
        if (!extractAll) result+="documentados ";
      }
      result+="com refer�ncias para ";
      if (extractAll)
        result+="seus respectivos arquivos:";
      else
        result+="suas respectivas documenta��es:";
      return result;
    }

    /*! This is an introduction to the page with the list of all examples */
    virtual QCString trExamplesDescription()
    { return "Esta � a lista com todos os exemplos:"; }

    /*! This is an introduction to the page with the list of related pages */
    virtual QCString trRelatedPagesDescription()
    { return "Esta � a lista com toda a documenta��o relacionadas:"; }

    /*! This is an introduction to the page with the list of class/file groups */
    virtual QCString trModulesDescription()
    { return "Esta � a lista com todos os m�dulos:"; }

    /*! This is used in HTML as the title of index.html. */
    virtual QCString trDocumentation()
    { return "\nDocumenta��o"; }

    /*! This is used in LaTeX as the title of the chapter with the
     * index of all groups.
     */
    virtual QCString trModuleIndex()
    { return "�ndice dos M�dulos"; }

    /*! This is used in LaTeX as the title of the chapter with the
     * class hierarchy.
     */
    virtual QCString trHierarchicalIndex()
    { return "�ndice Hier�rquico"; }

    /*! This is used in LaTeX as the title of the chapter with the
     * annotated compound index.
     */
    virtual QCString trCompoundIndex()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "�ndice das Estruturas de Dados";
      }
      else
      {
        return "�ndice dos Componentes";
      }
    }

    /*! This is used in LaTeX as the title of the chapter with the
     * list of all files.
     */
    virtual QCString trFileIndex()
    { return "�ndice dos Arquivos"; }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all groups.
     */
    virtual QCString trModuleDocumentation()
    { return "M�dulos"; }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all classes, structs and unions.
     */
    virtual QCString trClassDocumentation()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Estruturas";
      }
      else
      {
        return "Classes";
      }
    }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all files.
     */
    virtual QCString trFileDocumentation()
    { return "Arquivos"; }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all examples.
     */
    virtual QCString trExampleDocumentation()
    { return "Exemplos"; }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all related pages.
     */
    virtual QCString trPageDocumentation()
    { return "Documenta��o Relacionada"; }

    /*! This is used in LaTeX as the title of the document */
    virtual QCString trReferenceManual()
    { return "Guia de Refer�ncia"; }

    /*! This is used in the documentation of a file as a header before the
     *  list of defines
     */
    virtual QCString trDefines()
    { return "Defini��es e Macros"; }

    /*! This is used in the documentation of a file as a header before the
     *  list of function prototypes
     */
    virtual QCString trFuncProtos()
    { return "Prot�tipos de Fun��es"; }

    /*! This is used in the documentation of a file as a header before the
     *  list of typedefs
     */
    virtual QCString trTypedefs()
    { return "Defini��es de Tipos"; }

    /*! This is used in the documentation of a file as a header before the
     *  list of enumerations
     */
    virtual QCString trEnumerations()
    { return "Enumera��es"; }

    /*! This is used in the documentation of a file as a header before the
     *  list of (global) functions
     */
    virtual QCString trFunctions()
    { return "Fun��es"; }

    /*! This is used in the documentation of a file as a header before the
     *  list of (global) variables
     */
    virtual QCString trVariables()
    { return "Vari�veis"; }

    /*! This is used in the documentation of a file as a header before the
     *  list of (global) variables
     */
    virtual QCString trEnumerationValues()
    { return "Valores enumerados"; }

    /*! This is used in the documentation of a file before the list of
     *  documentation blocks for defines
     */
    virtual QCString trDefineDocumentation()
    { return "Defini��es e macros"; }

    /*! This is used in the documentation of a file/namespace before the list
     *  of documentation blocks for function prototypes
     */
    virtual QCString trFunctionPrototypeDocumentation()
    { return "Prot�tipos das fun��es"; }

    /*! This is used in the documentation of a file/namespace before the list
     *  of documentation blocks for typedefs
     */
    virtual QCString trTypedefDocumentation()
    { return "Defini��es dos tipos"; }

    /*! This is used in the documentation of a file/namespace before the list
     *  of documentation blocks for enumeration types
     */
    virtual QCString trEnumerationTypeDocumentation()
    { return "Enumera��es"; }

    /*! This is used in the documentation of a file/namespace before the list
     *  of documentation blocks for functions
     */
    virtual QCString trFunctionDocumentation()
    { return "Fun��es"; }

    /*! This is used in the documentation of a file/namespace before the list
     *  of documentation blocks for variables
     */
    virtual QCString trVariableDocumentation()
    { return "Vari�veis"; }

    /*! This is used in the documentation of a file/namespace/group before
     *  the list of links to documented compounds
     */
    virtual QCString trCompounds()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Estruturas de Dados";
      }
      else
      {
        return "Componentes";
      }
    }

    /*! This is used in the standard footer of each page and indicates when
     *  the page was generated
     */
    virtual QCString trGeneratedAt(const char *date,const char *projName)
    {
      QCString result=(QCString)"Gerado em "+date;
      if (projName) result+=(QCString)" para "+projName;
      result+=(QCString)" por";
      return result;
    }
    /*! This is part of the sentence used in the standard footer of each page.
     */
    virtual QCString trWrittenBy()
    {
      return "escrito por";
    }

    /*! this text is put before a class diagram */
    virtual QCString trClassDiagram(const char *clName)
    {
      return (QCString)"Diagrama de Hierarquia para "+clName+":";
    }

    /*! this text is generated when the \\internal command is used. */
    virtual QCString trForInternalUseOnly()
    { return "Apenas para uso interno."; }

    /*! this text is generated when the \\warning command is used. */
    virtual QCString trWarning()
    { return "Aviso"; }

    /*! this text is generated when the \\version command is used. */
    virtual QCString trVersion()
    { return "Vers�o"; }

    /*! this text is generated when the \\date command is used. */
    virtual QCString trDate()
    { return "Data"; }

    /*! this text is generated when the \\return command is used. */
    virtual QCString trReturns()
    { return "Retorna"; }

    /*! this text is generated when the \\sa command is used. */
    virtual QCString trSeeAlso()
    { return "Veja tamb�m"; }

    /*! this text is generated when the \\param command is used. */
    virtual QCString trParameters()
    { return "Par�metros"; }

    /*! this text is generated when the \\exception command is used. */
    virtual QCString trExceptions()
    { return "Exce��es"; }

    /*! this text is used in the title page of a LaTeX document. */
    virtual QCString trGeneratedBy()
    { return "Gerado por"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990307
//////////////////////////////////////////////////////////////////////////

    /*! used as the title of page containing all the index of all namespaces. */
    virtual QCString trNamespaceList()
    { return "Lista de Namespaces"; }

    /*! used as an introduction to the namespace list */
    virtual QCString trNamespaceListDescription(bool extractAll)
    {
      QCString result="Esta � a lista de todos os Namespaces ";
      if (!extractAll) result+="documentados ";
      result+="com suas respectivas descri��es:";
      return result;
    }

    /*! used in the class documentation as a header before the list of all
     *  friends of a class
     */
    virtual QCString trFriends()
    { return "Amigas"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990405
//////////////////////////////////////////////////////////////////////////

    /*! used in the class documentation as a header before the list of all
     * related classes
     */
    virtual QCString trRelatedFunctionDocumentation()
    { return "Amigas e Fun��es Relacionadas"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990425
//////////////////////////////////////////////////////////////////////////

    /*! used as the title of the HTML page of a class/struct/union */
    virtual QCString trCompoundReference(const char *clName,
                                    ClassDef::CompoundType compType,
                                    bool isTemplate)
    {
      QCString result="Refer�ncia da";
      if (isTemplate) result+=" Template de";
      switch(compType)
      {
        case ClassDef::Class:      result+=" Classe "; break;
        case ClassDef::Struct:     result+=" Estrutura "; break;
        case ClassDef::Union:      result+=" Uni�o "; break;
        case ClassDef::Interface:  result+=" Interface "; break;
        case ClassDef::Protocol:   result+=" Protocol "; break; // translate me!
        case ClassDef::Category:   result+=" Category "; break; // translate me!
        case ClassDef::Exception:  result+=" Exce��o "; break;
      }
      result+=(QCString)clName;
      return result;
    }

    /*! used as the title of the HTML page of a file */
    virtual QCString trFileReference(const char *fileName)
    {
      QCString result = "Refer�ncia do Arquivo ";
      result += fileName;
      return result;
    }

    /*! used as the title of the HTML page of a namespace */
    virtual QCString trNamespaceReference(const char *namespaceName)
    {
      QCString result ="Ref�ncia do Namespace ";
      result += namespaceName;
      return result;
    }

    virtual QCString trPublicMembers()
    { return "M�todos P�blicos"; }
    virtual QCString trPublicSlots()
    { return "Slots P�blicos"; }
    virtual QCString trSignals()
    { return "Sinais"; }
    virtual QCString trStaticPublicMembers()
    { return "M�todos P�blicos Est�ticos"; }
    virtual QCString trProtectedMembers()
    { return "M�todos Protegidos"; }
    virtual QCString trProtectedSlots()
    { return "Slots Protegidos"; }
    virtual QCString trStaticProtectedMembers()
    { return "M�todos Protegidos Est�ticos"; }
    virtual QCString trPrivateMembers()
    { return "M�todos Privados"; }
    virtual QCString trPrivateSlots()
    { return "Slots Privados"; }
    virtual QCString trStaticPrivateMembers()
    { return "M�todos Privados Est�ticos"; }

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
            result+=" e ";
        }
      }
      return result;
    }

    /*! used in class documentation to produce a list of base classes,
     *  if class diagrams are disabled.
     */
    virtual QCString trInheritsList(int numEntries)
    {
      return "Herdeiro de " + trWriteList(numEntries) + ".";
    }

    /*! used in class documentation to produce a list of super classes,
     *  if class diagrams are disabled.
     */
    virtual QCString trInheritedByList(int numEntries)
    {
      return "Superclasse de "+trWriteList(numEntries)+".";
    }

    /*! used in member documentation blocks to produce a list of
     *  members that are hidden by this one.
     */
    virtual QCString trReimplementedFromList(int numEntries)
    {
      return "Reimplementa��o de "+trWriteList(numEntries)+".";
    }

    /*! used in member documentation blocks to produce a list of
     *  all member that overwrite the implementation of this member.
     */
    virtual QCString trReimplementedInList(int numEntries)
    {
      return "Reimplementado por "+trWriteList(numEntries)+".";
    }

    /*! This is put above each page as a link to all members of namespaces. */
    virtual QCString trNamespaceMembers()
    { return "Membros do Namespace"; }

    /*! This is an introduction to the page with all namespace members */
    virtual QCString trNamespaceMemberDescription(bool extractAll)
    {
      QCString result="Esta � a lista com todos os membros do Namespace ";
      if (!extractAll) result+="documentados ";
      result+="com refer�ncias para ";
      if (extractAll)
        result+="a documenta��o de seus respectivos Namespaces:";
      else
        result+="os seus respectivos namespaces:";
      return result;
    }
    /*! This is used in LaTeX as the title of the chapter with the
     *  index of all namespaces.
     */
    virtual QCString trNamespaceIndex()
    { return "Namespaces"; }

    /*! This is used in LaTeX as the title of the chapter containing
     *  the documentation of all namespaces.
     */
    virtual QCString trNamespaceDocumentation()
    { return "Namespaces"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990522
//////////////////////////////////////////////////////////////////////////

    /*! This is used in the documentation before the list of all
     *  namespaces in a file.
     */
    virtual QCString trNamespaces()
    { return "Namespaces"; }

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
      QCString result=(QCString)"A documenta��o para esta ";
      switch(compType)
      {
        case ClassDef::Class:      result+="classe "; break;
        case ClassDef::Struct:     result+="estrutura "; break;
        case ClassDef::Union:      result+="uni�o "; break;
        case ClassDef::Interface:  result+="interface "; break;
        case ClassDef::Protocol:   result+="protocol "; break; // translate me!
        case ClassDef::Category:   result+="category "; break; // translate me!
        case ClassDef::Exception:  result+="exce��o "; break;
      }
      result+=" foi gerada a partir ";
      if (single) result+="do seguinte arquivo:"; else result+="dos seguintes arquivos:";
      return result;
    }

    /*! This is in the (quick) index as a link to the alphabetical compound
     * list.
     */
    virtual QCString trAlphabeticalList()
    { return "Lista Alfab�tica"; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-990901
//////////////////////////////////////////////////////////////////////////

    /*! This is used as the heading text for the retval command. */
    virtual QCString trReturnValues()
    { return "Valores Retornados"; }

    /*! This is in the (quick) index as a link to the main page (index.html)
     */
    virtual QCString trMainPage()
    { return "P�gina Principal"; }

    /*! This is used in references to page that are put in the LaTeX
     *  documentation. It should be an abbreviation of the word page.
     */
    virtual QCString trPageAbbreviation()
    { return "pag."; }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-991003
//////////////////////////////////////////////////////////////////////////

    virtual QCString trDefinedAtLineInSourceFile()
    {
      return "Defini��o na linha @0 do arquivo @1.";
    }
    virtual QCString trDefinedInSourceFile()
    {
      return "Defini��o no arquivo @0.";
    }

//////////////////////////////////////////////////////////////////////////
// new since 0.49-991205
//////////////////////////////////////////////////////////////////////////

    virtual QCString trDeprecated()
    {
      /*
      * This note is for brazilians only.
      * Esta � uma boa tradu��o para "deprecated"?
      */
      return "Descontinuado(a)";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.0.0
//////////////////////////////////////////////////////////////////////////

    /*! this text is put before a collaboration diagram */
    virtual QCString trCollaborationDiagram(const char *clName)
    {
      return (QCString)"Diagrama de colabora��o para "+clName+":";
    }
    /*! this text is put before an include dependency graph */
    virtual QCString trInclDepGraph(const char *fName)
    {
      return (QCString)"Gr�fico de depend�ncia de inclus�es para "+fName+":";
    }
    /*! header that is put before the list of constructor/destructors. */
    virtual QCString trConstructorDocumentation()
    {
      return "Construtores & Destrutores";
    }
    /*! Used in the file documentation to point to the corresponding sources. */
    virtual QCString trGotoSourceCode()
    {
      return "V� para o c�digo-fonte deste arquivo.";
    }
    /*! Used in the file sources to point to the corresponding documentation. */
    virtual QCString trGotoDocumentation()
    {
      return "V� para a documenta��o deste arquivo.";
    }
    /*! Text for the \\pre command */
    virtual QCString trPrecondition()
    {
      return "Pr�-Condi��o";
    }
    /*! Text for the \\post command */
    virtual QCString trPostcondition()
    {
      return "P�s-Condi��o";
    }
    /*! Text for the \\invariant command */
    virtual QCString trInvariant()
    {
      return "Invariante";
    }
    /*! Text shown before a multi-line variable/enum initialization */
    virtual QCString trInitialValue()
    {
      return "Valor Inicial:";
    }
    /*! Text used the source code in the file index */
    virtual QCString trCode()
    {
      return "c�digo";
    }
    virtual QCString trGraphicalHierarchy()
    {
      return "Gr�fico de Hierarquia de Classes";
    }
    virtual QCString trGotoGraphicalHierarchy()
    {
      return "V� para o Gr�fico de Hierarquia de Classes";
    }
    virtual QCString trGotoTextualHierarchy()
    {
      return "V� para a Hierarquia de Classes (texto)";
    }
    virtual QCString trPageIndex()
    {
      return "�ndice da P�gina";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.1.0
//////////////////////////////////////////////////////////////////////////

    virtual QCString trNote()
    {
      return "Observa��o";
    }
    virtual QCString trPublicTypes()
    {
      return "Tipos P�blicos";
    }
    virtual QCString trPublicAttribs()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Campos de Dados";
      }
      else
      {
        return "Atributos P�blicos";
      }
    }
    virtual QCString trStaticPublicAttribs()
    {
      return "Atributos Est�ticos P�blicos";
    }
    virtual QCString trProtectedTypes()
    {
      return "Tipos Protegidos";
    }
    virtual QCString trProtectedAttribs()
    {
      return "Atributos Protegidos";
    }
    virtual QCString trStaticProtectedAttribs()
    {
      return "Atributos Est�ticos Protegidos";
    }
    virtual QCString trPrivateTypes()
    {
      return "Tipos Privados";
    }
    virtual QCString trPrivateAttribs()
    {
      return "Atributos Privados";
    }
    virtual QCString trStaticPrivateAttribs()
    {
      return "Atributos Privados Est�ticos";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.1.3
//////////////////////////////////////////////////////////////////////////

    /*! Used as a marker that is put before a todo item */
    virtual QCString trTodo()
    {
      return "Futuras Atividades";
    }
    /*! Used as the header of the todo list */
    virtual QCString trTodoList()
    {
      return "Lista de Futuras Atividades";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.1.4
//////////////////////////////////////////////////////////////////////////

    virtual QCString trReferencedBy()
    {
      return "Referenciado por";
    }
    virtual QCString trRemarks()
    {
      return "Anota��es";
    }
    virtual QCString trAttention()
    {
      return "Aten��o";
    }
    virtual QCString trInclByDepGraph()
    {
      return "Este grafo mostra quais arquivos est�o direta ou indiretamente relacionados com este arquivo:";
    }
    virtual QCString trSince()
    {
      return "Desde";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.1.5
//////////////////////////////////////////////////////////////////////////

    /*! title of the graph legend page */
    virtual QCString trLegendTitle()
    {
      return "Legenda do Grafo";
    }
    /*! page explaining how the dot graph's should be interpreted */
    virtual QCString trLegendDocs()
    {
      return
        "Esta p�gina explica como interpretar os grafos gerados pelo doxygen.<p>\n"
        "Considere o seguinte exemplo:\n"
        "\\code\n"
        "/*! Invisible class because of truncation */\n"
        "class Invisible { };\n\n"
        "/*! Truncated class, inheritance relation is hidden */\n"
        "class Truncated : public Invisible { };\n\n"
        "/* Class not documented with doxygen comments */\n"
        "class Undocumented { };\n\n"
        "/*! Class that is inherited using public inheritance */\n"
        "class PublicBase : public Truncated { };\n\n"
        "/*! A template class */\n"
        "template<class T> class Templ { };\n\n"
        "/*! Class that is inherited using protected inheritance */\n"
        "class ProtectedBase { };\n\n"
        "/*! Class that is inherited using private inheritance */\n"
        "class PrivateBase { };\n\n"
        "/*! Class that is used by the Inherited class */\n"
        "class Used { };\n\n"
        "/*! Super class that inherits a number of other classes */\n"
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

        "Se a tag \\c MAX_DOT_GRAPH_HEIGHT no arquivo de configura��o tem o valor"
        "200, o seguinte gr�fo ser� gerado:"
        "<p><center><img src=\"graph_legend."+Config_getEnum("DOT_IMAGE_FORMAT")+"\"></center>\n"
        "<p>\n"
        "As caixas no grafo acima tem as seguintes interpreta��es:\n"
        "<ul>\n"
        "<li>Uma caixa inteiramente preta representa a estrutura ou a classe para qual "
        "o grafo foi gerado.\n"
        "<li>Uma caixa com bordas pretas denota uma estrutura ou classe documentada.\n"
        "<li>Uma caixa com bordas cinzas denota uma estrutura ou classe n�o documentada.\n"

        "<li>Uma caixa com bordas vermelhas denota uma estrutura ou classe documentada para\n"
        "a qual nem todas as heran�as ou componentes s�o mostradas no grafo. Um grafo � "
        "truncado quando este � maior que o tamanho especificado."
        "</ul>\n"
        "As setas tem os seguintes significados:\n"
        "<ul>\n"
        "<li>Uma seta azul escura � utilizada para denotar uma rela��o de heran�a "
        "p�blica entre duas classes.\n"
        "<li>Uma seta verde escura � utilizada para denotar uma heran�a protegida.\n"
        "<li>Uma seta vermelho escura � utilizada para denotar uma heran�a privada.\n"
        "<li>Uma seta p�rpura pontilhada � usada se uma classe est� contida ou � utilizada"
        "por outra classe. A seta � marcada com a(s) vari�vel(eis) "
        "atrav�s das quais a classe ou estrutura apontada est� acess�vel. \n"
        "</ul>\n";
    }
    /*! text for the link to the legend page */
    virtual QCString trLegend()
    {
      return "legenda";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.0
//////////////////////////////////////////////////////////////////////////

    /*! Used as a marker that is put before a test item */
    virtual QCString trTest()
    {
      return "Teste";
    }
    /*! Used as the header of the test list */
    virtual QCString trTestList()
    {
      return "Lista de Testes";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.1
//////////////////////////////////////////////////////////////////////////

    /*! Used as a section header for KDE-2 IDL methods */
    virtual QCString trDCOPMethods()
    {
      return "M�todos DCOP";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.2
//////////////////////////////////////////////////////////////////////////

    /*! Used as a section header for IDL properties */
    virtual QCString trProperties()
    {
      return "Propriedades";
    }
    /*! Used as a section header for IDL property documentation */
    virtual QCString trPropertyDocumentation()
    {
      return "Propriedades";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.4
//////////////////////////////////////////////////////////////////////////

    /*! Used for Java classes in the summary section of Java packages */
    virtual QCString trClasses()
    {
      if (Config_getBool("OPTIMIZE_OUTPUT_FOR_C"))
      {
        return "Estruturas de Dados";
      }
      else
      {
        return "Classes";
      }
    }
    /*! Used as the title of a Java package */
    virtual QCString trPackage(const char *name)
    {
      return (QCString)"Pacote "+name;
    }
    /*! Title of the package index page */
    virtual QCString trPackageList()
    {
      return "Lista de Pacotes";
    }
    /*! The description of the package index page */
    virtual QCString trPackageListDescription()
    {
      return "Esta � a lista com os pacotes e suas respectivas descri��es (se dispon�veis):";
    }
    /*! The link name in the Quick links header for each page */
    virtual QCString trPackages()
    {
      return "Pacotes";
    }
    /*! Text shown before a multi-line define */
    virtual QCString trDefineValue()
    {
      return "Valor:";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.5
//////////////////////////////////////////////////////////////////////////

    /*! Used as a marker that is put before a \\bug item */
    virtual QCString trBug()
    {
      return "Problema";
    }
    /*! Used as the header of the bug list */
    virtual QCString trBugList()
    {
      return "Lista de Problemas";
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
      return "0";
    }

    /*! Used as header RTF general index */
    virtual QCString trRTFGeneralIndex()
    {
      return "�ndice";
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names
     *  of the category.
     */
    virtual QCString trClass(bool first_capital, bool singular)
    {
      QCString result((first_capital ? "Classe" : "classe"));
      if (!singular)  result+="s";
      return result;
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names
     *  of the category.
     */
    virtual QCString trFile(bool first_capital, bool singular)
    {
      QCString result((first_capital ? "Arquivo": "arquivo"));
      if (!singular)  result+="s";
      return result;
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names
     *  of the category.
     */
    virtual QCString trNamespace(bool first_capital, bool singular)
    {
      QCString result((first_capital ? "Namespace" : "namespace"));
      if (!singular)  result+="s";
      return result;
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names
     *  of the category.
     */
    virtual QCString trGroup(bool first_capital, bool singular)
    {
      QCString result((first_capital ? "Grupo" : "grupo"));
      if (!singular)  result+="s";
      return result;
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names
     *  of the category.
     */
    virtual QCString trPage(bool first_capital, bool singular)
    {
      QCString result((first_capital ? "P�gina" : "p�gina"));
      if (!singular)  result+="s";
      return result;
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names
     *  of the category.
     */
    virtual QCString trMember(bool first_capital, bool singular)
    {
      QCString result((first_capital ? "Membro" : "membro"));
      if (!singular)  result+="s";
      return result;
    }

    /*! This is used for translation of the word that will possibly
     *  be followed by a single name or by a list of names
     *  of the category.
     */
    virtual QCString trGlobal(bool first_capital, bool singular)
    {
      QCString result((first_capital ? "Globa" : "globa"));
      if (!singular){
        result+="is";
      }else{
        result+="l";
      }
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
      if (!singular)  result+="es";
      return result;
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.11
//////////////////////////////////////////////////////////////////////////

    /*! This text is put before the list of members referenced by a member
     */
    virtual QCString trReferences()
    {
      return "Refer�ncias";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.13
//////////////////////////////////////////////////////////////////////////

    /*! used in member documentation blocks to produce a list of
     *  members that are implemented by this one.
     */
    virtual QCString trImplementedFromList(int numEntries)
    {
      return "Implementa "+trWriteList(numEntries)+".";
    }

    /*! used in member documentation blocks to produce a list of
     *  all members that implementation this member.
     */
    virtual QCString trImplementedInList(int numEntries)
    {
      return "Implementado por "+trWriteList(numEntries)+".";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.16
//////////////////////////////////////////////////////////////////////////

    /*! used in RTF documentation as a heading for the Table
     *  of Contents.
     */
    virtual QCString trRTFTableOfContents()
    {
      return "Conte�do";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.17
//////////////////////////////////////////////////////////////////////////

    /*! Used as the header of the list of item that have been
     *  flagged deprecated
     */
    virtual QCString trDeprecatedList()
    {
      return "Lista de Descontinuados(as)";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.2.18
//////////////////////////////////////////////////////////////////////////

    /*! Used as a header for declaration section of the events found in
     * a C# program
     */
    virtual QCString trEvents()
    {
      return "Eventos";
    }
    /*! Header used for the documentation section of a class' events. */
    virtual QCString trEventDocumentation()
    {
      return "Eventos";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.3
//////////////////////////////////////////////////////////////////////////

    /*! Used as a heading for a list of Java class types with package scope.
     */
    virtual QCString trPackageTypes()
    {
      return "Tipos do Pacote";
    }

    /*! Used as a heading for a list of Java class functions with package
     * scope.
     */
    virtual QCString trPackageMembers()
    {
      return "Fun��es do Pacote";
    }

    /*! Used as a heading for a list of static Java class functions with
     *  package scope.
     */
    virtual QCString trStaticPackageMembers()
    {
      return "Fun��es Est�ticas do Pacote";
    }

    /*! Used as a heading for a list of Java class variables with package
     * scope.
     */
    virtual QCString trPackageAttribs()
    {
      return "Atributos do Pacote";
    }

    /*! Used as a heading for a list of static Java class variables with
     * package scope.
     */
    virtual QCString trStaticPackageAttribs()
    {
      return "Atributos Est�ticos do Pacote";
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.3.1
//////////////////////////////////////////////////////////////////////////

    /*! Used in the quick index of a class/file/namespace member list page
     *  to link to the unfiltered list of all members.
     */
    virtual QCString trAll()
    {
      return "Todos";
    }
    /*! Put in front of the call graph for a function. */
    virtual QCString trCallGraph()
    {
      return "Este � o grafo de chamadas para esta fun��o:";
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
      return "Procurar por";
    }
    /*! This string is used as the title for the page listing the search
     *  results.
     */
    virtual QCString trSearchResultsTitle()
    {
      return "Resultado da Busca";
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
        return "Nenhum documento foi encontrado.";
      }
      else if (numDocuments==1)
      {
        return "Apenas <b>1</b> documento foi encontrado.";
      }
      else
      {
        return "<b>$num</b> documentos encontrados. "
               "Os melhores resultados vem primeiro.";
      }
    }
    /*! This string is put before the list of matched words, for each search
     *  result. What follows is the list of words that matched the query.
     */
    virtual QCString trSearchMatches()
    {
      return "Resultados:";
    }
    
//////////////////////////////////////////////////////////////////////////
// new since 1.3.8
//////////////////////////////////////////////////////////////////////////

    /*! This is used in HTML as the title of page with source code for file filename
     */
    virtual QCString trSourceFile(QCString& filename)
    {
      return  "C�digo-Fonte de " + filename;
    }

//////////////////////////////////////////////////////////////////////////
// new since 1.3.9
//////////////////////////////////////////////////////////////////////////

    /*! This is used as the name of the chapter containing the directory
     *  hierarchy.
     */
    virtual QCString trDirIndex()
    { return "Hierarquia de Diret�rios"; }

    /*! This is used as the name of the chapter containing the documentation
     *  of the directories.
     */
    virtual QCString trDirDocumentation()
    { return "Documenta��o do Direct�rio"; }

    /*! This is used as the title of the directory index and also in the
     *  Quick links of a HTML page, to link to the directory hierarchy.
     */
    virtual QCString trDirectories()
    { return "Diret�rios"; }

    /*! This returns a sentences that introduces the directory hierarchy. 
     *  and the fact that it is sorted alphabetically per level
     */
    virtual QCString trDirDescription()
    { return "Esta Hierarquia de Diret�rios est� parcialmente ordenada (ordem alfab�tica)"; }

    /*! This returns the title of a directory page. The name of the
     *  directory is passed via \a dirName.
     */
    virtual QCString trDirReference(const char *dirName)
    {
        QCString result = "Refer�ncia do diret�rio ";
     	result += dirName;
     	return result;
    }

    /*! This returns the word directory with or without starting capital
     *  (\a first_capital) and in sigular or plural form (\a singular).
     */
    virtual QCString trDir(bool first_capital, bool singular)
    { 
      QCString result((first_capital ? "Diret�rio" : "diret�rio"));
      if (!singular) result+="s";
      return result; 
    }
//////////////////////////////////////////////////////////////////////////
// new since 1.4.1
//////////////////////////////////////////////////////////////////////////

    /*! This text is added to the documentation when the \\overload command
     *  is used for a overloaded function.
     */
    virtual QCString trOverloadText()
    {
       return "Este � um m�todo provido por conveni�ncia. "
       		"Ele difere do m�todo acima apenas na lista de "
       		"argumentos que devem ser utilizados.";
    }    

//////////////////////////////////////////////////////////////////////////
// new since 1.4.6
//////////////////////////////////////////////////////////////////////////

    /*! This is used to introduce a caller (or called-by) graph */
    virtual QCString trCallerGraph()
    {
      return "Este � o diagrama de chamadas para esta fun��o:";
    }

    /*! This is used in the documentation of a file/namespace before the list 
     *  of documentation blocks for enumeration values
     */
    virtual QCString trEnumerationValueDocumentation()
    { return "Documenta��o da enumera��o"; }
  
};
#endif
