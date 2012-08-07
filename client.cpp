/////////////////////////////////////////////////////////////////////////////
// Name:         client.cpp
// Purpose:      File principale di Connection Alive 1.6
// Author:       Sebastiano Dimartina <connectionalive@softhome.net>
// Modified by:
// Created:      2004/11/xx
// RCS-ID:
// Copyright:    (c) 2003 Integra di Sebastiano Dimartina
// Licence:      wxWindows licence
// Thanks to:    Guillermo Rodriguez Garcia <guille@iies.es>
//               Vaclav Slavik (v.slavik@volny.cz)
//               Julian Smart
//               Vadim Zeitlin
/////////////////////////////////////////////////////////////////////////////
        

#if defined(__GNUG__) && !defined(__APPLE__)
#  pragma implementation "client.cpp"
#  pragma interface "client.cpp"
#endif


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#  pragma hdrstop
#endif

#ifndef WX_PRECOMP
#  include "wx/wx.h"
#endif

#include "wx/string.h"
#include "wx/utils.h"
#include "wx/timer.h"
#include "wx/pen.h"
#include "wx/socket.h"
#include "wx/url.h"
#include "wx/wfstream.h"
#include "wx/wxhtml.h"
#include "wx/statline.h"
#include "wx/menuitem.h"
#include "wx/notebook.h"
#include "wx/log.h"
#include "wx/config.h"
#include "wx/thread.h"
#include "wx/wizard.h"
#include "wx/busyinfo.h"
#include "wx/minifram.h"
#include "wx/taskbar.h"
#include "wx/splash.h"
#include "wx/process.h"
#include "wx/dialup.h"
#include "myclasses.h"



// --------------------------------------------------------------------------
// vars per classe WxConfig() ...
// --------------------------------------------------------------------------

wxCheckBox      *Master_chk1,
                *Master_chk2,
                *Master_chk3,
                *Connect_chk1,
                *Connect_chk2;

wxTextCtrl      *nomelogfile,
                *control1,
                *control2;

wxRadioBox      *Master_radio1,
                *m_radioTextLines;

wxSlider        *m_slider;
wxListBox       *m_listbox;
wxChoice        *m_choice;



// --------------------------------------------------------------------------
// risorse
// --------------------------------------------------------------------------

#if defined(__WXGTK__) || defined(__WXX11__) || defined(__WXMOTIF__) || defined(__WXMAC__)
#  include "mondrian.xpm"
#endif




// --------------------------------------------------------------------------
// classi
// --------------------------------------------------------------------------

class MyApp : public wxApp
{
public:
  virtual bool OnInit();
  virtual bool ToolbarIstogramma(wxToolBar* toolBar);

protected:
    MyTaskBarIcon   m_taskBarIcon;
};





class MyFrame : public wxFrame
{
public:
  MyFrame();
 ~MyFrame();
  void  OnQuit(wxCommandEvent& event);
  void  OnAbout(wxCommandEvent& event);
  void  LanciaCalcolatrice(wxCommandEvent& event);
  void  OnCommutaToolbar(wxCommandEvent& event);
  void  OnRingraziamenti(wxCommandEvent& event);
  void  OnSorgenti(wxCommandEvent& event);
  void  OnIndex(wxCommandEvent& event);
  void  OnOpenConnection(wxCommandEvent& event);
  void  OnRitardo(wxCommandEvent& event);
  void  OnOpzioni(wxCommandEvent& event);
  void  OnIdentificazione(wxCommandEvent& event);
  void  OnSalvaOpzioniMaster(wxCommandEvent& event);
  void  OnSalvaOpzioniLogFile(wxCommandEvent& event);
  void  OnSalvaOpzioniConnessione(wxCommandEvent& event);
  void  OnSalvaOpzioniIdentita(wxCommandEvent& event);
  void  OnSalvaOpzioniIntervallo(wxCommandEvent& event);
  void  Onintervallo(wxCommandEvent& event);
  void  OnLogFile(wxCommandEvent& event);
  void  OnConnessione(wxCommandEvent& event);
  void  OnScegliLogFile(wxCommandEvent& event);
  void  OnPing(wxCommandEvent& event);
  void  OnCloseConnection(wxCommandEvent& event);
  bool  LogAnalitico();
  bool  IdleLoop();
  void  NascondiToolbar();
  void  VisualizzaHelpIstogramma();
  void  Onstatistiche(wxCommandEvent& WXUNUSED(event));
  void  Statistiche();
  void  CommutaPing(wxCommandEvent& WXUNUSED(event));
  void  ChiudiTCP();
  void  SalvaCoord();
  void  ScriviRitardo(long param);
  void  ScriviTimeout(long param);
  void  PingExec(void);
  void  OnRunWizard(wxCommandEvent& event);
  void  PulisciLogFile(wxCommandEvent& event);
  void  UltimoLog(wxCommandEvent& event);
  void  AumentaRitardo(wxCommandEvent& event);
  void  DiminuisciRitardo(wxCommandEvent& event);
  void  AumentaCaricoPing(wxCommandEvent& event);
  void  DiminuisciCaricoPing(wxCommandEvent& event);
  void  NascondiFrame(wxCommandEvent& event);
  void  ElencaIsp(wxCommandEvent& event);
  void  Dial(wxCommandEvent& event);
  void  ControllaConnessione(wxCommandEvent& event);
  void  AgganciaTelecomando(wxCommandEvent& WXUNUSED(event));
  void  NascondiTelecomando(wxCommandEvent& WXUNUSED(event));
  void  CommutaBell(wxCommandEvent& WXUNUSED(event));
  void  CommutaBMP(wxCommandEvent& WXUNUSED(event));
  void  CommutaColore(wxCommandEvent& WXUNUSED(event));
  void  OnSocketEvent(wxSocketEvent& event);
  void  OnTimeout(wxCommandEvent& event);
  void  VisualizzaIstogramma(wxCommandEvent& WXUNUSED(event));
  long  Ritorna_NumeroDownloads();
  long  Ritorna_millisec_indice();
  float Ritorna_media_totale();
  int   Ritorna_riduzione_istogramma();
  void  MostraFrame(wxCommandEvent& event);
  bool  MostraRAM();
  bool  MostraBMPIstogramma();
  bool  MostraColoreIstogramma();
  void  MostraToolbar();
  bool  MostraPing();
  long  millisec_serie[20+1];


private:
  wxMenuItem      *Menu1;
  wxMenuItem      *Menu2;
  wxMenuItem      *Menu3;
  wxToolBar       *toolBar;
  wxDialUpManager *m_dial;
  wxSocketClient  *m_sock;
  wxTextCtrl      *m_text;
  wxMenu          *m_menuFile;
  wxMenu          *m_menuEdit;
  wxMenu          *m_menuConnessione;
  wxMenu          *m_SubMenu;
  wxMenu          *m_menuInfo;
  wxMenuBar       *m_menuBar;

  long             m_SecRitardo;
  long             m_Carico_Ping;
  long             millisecondi;
  long             m_Timeout;
  int              larghezza_win;
  int              altezza_win;
  float            millisecondi_complessivi;

  bool             s_abilitato;
  bool             t_abilitato;
  bool             i_abilitato;
  bool             h_abilitato;
  bool             b_abilitato;
  bool             Coordinate;

  long             ping_counter;
  long             millisec_indice;
  float            media_totale;
  bool             m_PingLoop;
  bool             p_abilitato;
  bool             c_abilitato;

  DECLARE_EVENT_TABLE()
};

MyFrame        * frame;





// --------------------------------------------------------------------------
// constanti
// --------------------------------------------------------------------------

enum
{
  CLIENT_QUIT = 1000,
  CLIENT_ABOUT,
  CLIENT_LANCIACALCOLATRICE,
  CLIENT_COMMUTA_TOOLBAR,
  CLIENT_RINGRAZIAMENTI,
  CLIENT_SORGENTI,
  CLIENT_INDEX,
  CLIENT_RITARDO,
  CLIENT_OPZIONI,
  CLIENT_SCEGLILOGFILE,
  CLIENT_PING,
  CLIENT_CLOSE,
  CLIENT_DGRAM,
  CLIENT_LOG_RICARICA,
  CLIENT_IDENTIFICAZIONE,
  CLIENT_SALVAOPZIONILOGFILE,
  CLIENT_SALVAOPZIONICONNESSIONE,
  CLIENT_SALVAOPZIONIIDENTITA,
  CLIENT_SALVAOPZIONIINTERVALLO,
  CLIENT_SALVAOPZIONIMASTER,
  CLIENT_INTERVALLO,
  CLIENT_LOGFILE,
  CLIENT_CONNESSIONE,
  CLIENT_STATISTICHE,
  WIZARD_RUN,
  CLIENT_PULISCILOGFILE,
  CLIENT_ULTIMOLOG,
  CLIENT_AUMENTARITARDO,
  CLIENT_DIMUISCIRITARDO,
  CLIENT_CARICO,
  CLIENT_DIMUISCICARICO,
  ID_SHOWNAV,
  ID_ORIGIN,
  ID_CENTER,
  ID_NORTH,
  ID_SOUTH,
  ID_EAST,
  ID_WEST,
  PU_RESTORE,
  PU_NEW_ICON,
  PU_EXIT,
  PU_OPZIONI,
  PU_ABOUT,
  CLIENT_NASCONDIFRAME,
  CLIENT_ELENCAISP,
  CLIENT_DIAL,
  CONTROLLA_CONNESSIONE,
  CLIENT_MOSTRAFRAME,
  AGGANCIA_TELECOMANDO,
  NASCONDI_TELECOMANDO,
  MOSTRA_ISTOGRAMMA,
  ID_SUB_MENU,
  CLIENT_TIMEOUT,
  CLIENT_COMMUTA_PING,
  CLIENT_COMMUTA_BELL,
  CLIENT_COMMUTA_BMP,
  CLIENT_COMMUTA_COLORE,
  ID_TOOLBAR,
  ID_REPARENT,
  SOCKET_ID
};



// --------------------------------------------------------------------------
// Tabella EVENT  e macro per toolbar ...
// --------------------------------------------------------------------------

#define ADD_TOOL(id, bmp, tooltip, help)    toolBar->AddTool(id, bmp, wxNullBitmap, FALSE, -1, -1, (wxObject *)0, tooltip, help)



BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(CLIENT_QUIT,                     MyFrame::OnQuit)
  EVT_MENU(CLIENT_ABOUT,                    MyFrame::OnAbout)
  EVT_MENU(CLIENT_LANCIACALCOLATRICE,       MyFrame::LanciaCalcolatrice)
  EVT_MENU(CLIENT_COMMUTA_TOOLBAR,          MyFrame::OnCommutaToolbar)
  EVT_MENU(CLIENT_RINGRAZIAMENTI,           MyFrame::OnRingraziamenti)
  EVT_MENU(CLIENT_SORGENTI,                 MyFrame::OnSorgenti)
  EVT_MENU(CLIENT_INDEX,                    MyFrame::OnIndex)
  EVT_MENU(CLIENT_RITARDO,                  MyFrame::OnRitardo)
  EVT_MENU(CLIENT_OPZIONI,                  MyFrame::OnOpzioni)
  EVT_MENU(CLIENT_IDENTIFICAZIONE,          MyFrame::OnIdentificazione)
  EVT_MENU(CLIENT_SALVAOPZIONIIDENTITA,     MyFrame::OnSalvaOpzioniIdentita)
  EVT_MENU(CLIENT_SALVAOPZIONIINTERVALLO,   MyFrame::OnSalvaOpzioniIntervallo)
  EVT_MENU(CLIENT_SALVAOPZIONILOGFILE,      MyFrame::OnSalvaOpzioniLogFile)
  EVT_MENU(CLIENT_SALVAOPZIONICONNESSIONE,  MyFrame::OnSalvaOpzioniConnessione)
  EVT_MENU(CLIENT_SALVAOPZIONIMASTER,       MyFrame::OnSalvaOpzioniMaster)
  EVT_MENU(CLIENT_INTERVALLO,               MyFrame::Onintervallo)
  EVT_MENU(CLIENT_LOGFILE,                  MyFrame::OnLogFile)
  EVT_MENU(CLIENT_CONNESSIONE,              MyFrame::OnConnessione)
  EVT_MENU(CLIENT_SCEGLILOGFILE,            MyFrame::OnScegliLogFile)
  EVT_MENU(CLIENT_PING,                     MyFrame::OnPing)
  EVT_MENU(CLIENT_CLOSE,                    MyFrame::OnCloseConnection)
  EVT_MENU(CLIENT_STATISTICHE,              MyFrame::Onstatistiche)
  EVT_MENU(WIZARD_RUN,                      MyFrame::OnRunWizard)
  EVT_MENU(CLIENT_PULISCILOGFILE,           MyFrame::PulisciLogFile)
  EVT_MENU(CLIENT_ULTIMOLOG,                MyFrame::UltimoLog)
  EVT_BUTTON(ID_NORTH,                      MyFrame::AumentaRitardo)
  EVT_BUTTON(ID_SOUTH,                      MyFrame::DiminuisciRitardo)
  EVT_BUTTON(ID_CENTER,                     MyFrame::CommutaPing)
  EVT_BUTTON(ID_WEST,                       MyFrame::DiminuisciCaricoPing)
  EVT_BUTTON(ID_EAST,                       MyFrame::AumentaCaricoPing)
  EVT_MENU(CLIENT_NASCONDIFRAME,            MyFrame::NascondiFrame)
  EVT_MENU(CLIENT_ELENCAISP,                MyFrame::ElencaIsp)
  EVT_MENU(CLIENT_DIAL,                     MyFrame::Dial)
  EVT_MENU(CONTROLLA_CONNESSIONE,           MyFrame::ControllaConnessione)
  EVT_MENU(AGGANCIA_TELECOMANDO,            MyFrame::AgganciaTelecomando)
  EVT_MENU(NASCONDI_TELECOMANDO,            MyFrame::NascondiTelecomando)
  EVT_MENU(MOSTRA_ISTOGRAMMA,               MyFrame::VisualizzaIstogramma)
  EVT_MENU(CLIENT_COMMUTA_BELL,             MyFrame::CommutaBell)
  EVT_MENU(CLIENT_COMMUTA_BMP,              MyFrame::CommutaBMP)
  EVT_MENU(CLIENT_COMMUTA_COLORE,           MyFrame::CommutaColore)
  EVT_SOCKET(SOCKET_ID,                     MyFrame::OnSocketEvent)
  EVT_MENU(CLIENT_TIMEOUT,                  MyFrame::OnTimeout)
  EVT_MENU(CLIENT_COMMUTA_PING,             MyFrame::CommutaPing)
END_EVENT_TABLE()



BEGIN_EVENT_TABLE(MyButton, wxButton)
  EVT_BUTTON(CLIENT_INTERVALLO,             MyFrame::Onintervallo)
  EVT_BUTTON(CLIENT_LOGFILE,                MyFrame::OnLogFile)
  EVT_BUTTON(CLIENT_CONNESSIONE,            MyFrame::OnConnessione)
  EVT_BUTTON(CLIENT_IDENTIFICAZIONE,        MyFrame::OnIdentificazione)
  EVT_BUTTON(CLIENT_SALVAOPZIONIIDENTITA,   MyFrame::OnSalvaOpzioniIdentita)
  EVT_BUTTON(CLIENT_SALVAOPZIONIINTERVALLO, MyFrame::OnSalvaOpzioniIntervallo)
  EVT_BUTTON(CLIENT_SALVAOPZIONILOGFILE,    MyFrame::OnSalvaOpzioniLogFile)
  EVT_BUTTON(CLIENT_SALVAOPZIONICONNESSIONE,MyFrame::OnSalvaOpzioniConnessione)
  EVT_BUTTON(CLIENT_SALVAOPZIONIMASTER,     MyFrame::OnSalvaOpzioniMaster)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(PaginaWizard2, wxWizardPageSimple)
  EVT_WIZARD_PAGE_CHANGING(-1,              PaginaWizard2::OnWizardPageChanging)
  EVT_WIZARD_CANCEL       (-1,              PaginaWizard2::OnWizardCancel)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(PaginaWizard4, wxWizardPageSimple)
  EVT_WIZARD_PAGE_CHANGING(-1,              PaginaWizard4::OnWizardPageChanging)
  EVT_WIZARD_CANCEL       (-1,              PaginaWizard4::OnWizardCancel)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(PaginaWizard5, wxWizardPageSimple)
  EVT_WIZARD_PAGE_CHANGING(-1,              PaginaWizard5::OnWizardPageChanging)
  EVT_WIZARD_CANCEL       (-1,              PaginaWizard5::OnWizardCancel)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(Telecomando, wxMiniFrame)
  EVT_CLOSE(Telecomando::OnClose)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(MyTaskBarIcon, wxTaskBarIcon)
  EVT_MENU(PU_ABOUT,                        MyFrame::OnAbout)
  EVT_MENU(PU_OPZIONI,                      MyFrame::OnOpzioni)
  EVT_MENU(PU_NEW_ICON,                     MyTaskBarIcon::OnMenuSetNewIcon)
  EVT_MENU(CLIENT_MOSTRAFRAME,              MyFrame::MostraFrame)
  EVT_MENU(AGGANCIA_TELECOMANDO,            MyFrame::AgganciaTelecomando)
  EVT_MENU(CLIENT_INDEX,                    MyFrame::OnIndex)
END_EVENT_TABLE()




IMPLEMENT_APP(MyApp)

bool MyApp::ToolbarIstogramma(wxToolBar* toolBar)
{

  wxBitmap bitmap;
  wxBitmap bitmap2;

  bitmap.LoadFile("bitmaps/back_istogramma.bmp", wxBITMAP_TYPE_BMP);
  toolBar->AddTool(CLIENT_COMMUTA_BMP,    bitmap, wxNullBitmap, FALSE, 1, -1, (wxObject *) NULL, _T("Sfondo grafico"));

  bitmap.LoadFile("bitmaps/mono_istogramma.bmp", wxBITMAP_TYPE_BMP);
  toolBar->AddTool(CLIENT_COMMUTA_COLORE, bitmap, wxNullBitmap, FALSE, 1, -1, (wxObject *) NULL, _T("Colore/BN"));
  toolBar->Realize();

  return TRUE;

}



bool MyApp::OnInit()
{

  wxIcon icon(wxT("mondrian"));
  if (!m_taskBarIcon.SetIcon(icon, wxT("Connection Alive")))
      wxMessageBox(wxT("Impossibile settare l'icona."));

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetRecordDefaults();


  wxBitmap bitmap;
  if (bitmap.LoadFile("bitmaps/splash.bmp", wxBITMAP_TYPE_BMP))
  {

      new wxSplashScreen(bitmap,
          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
          2000, NULL, -1, wxDefaultPosition, wxDefaultSize,
          wxSIMPLE_BORDER|wxSTAY_ON_TOP);
  }

  frame = new MyFrame();
  frame->Show(TRUE);
  frame->CentreOnScreen(wxBOTH);
  SetTopWindow(frame);

  mini_frame = new CanvasParent(frame, -1, _T("Istogramma"), wxPoint(0,0), wxSize(133, 71));
  mini_frame->CreateToolBar(wxNO_BORDER|wxTB_VERTICAL, ID_TOOLBAR);
  ToolbarIstogramma(mini_frame->GetToolBar());
  mini_frame->SetIcon(wxICON(mondrian));
  mini_frame->Show(FALSE);

  return TRUE;

}





// --------------------------------------------------------------------------
// Istogramma
// --------------------------------------------------------------------------

BEGIN_EVENT_TABLE(Istogramma, wxScrolledWindow)
  EVT_PAINT(Istogramma::OnPaint)
END_EVENT_TABLE()

Istogramma::Istogramma(CanvasParent *parent)
        : wxScrolledWindow(parent, -1, wxDefaultPosition, wxDefaultSize)
{
}



void Istogramma::DisegnaIstogramma()
{

    static const int     TAB_H =  8;
    static const int     TAB_V = 44;
    wxPoint vertice[81];

    wxPaintDC dc(this);


    wxBitmap bitmap;

    if (frame->MostraBMPIstogramma())
    {
       if (frame->IdleLoop() == TRUE)
       {
          if (bitmap.LoadFile("bitmaps/backgnd1.bmp", wxBITMAP_TYPE_BMP))
             dc.DrawBitmap(bitmap, 0, 0);
       }
       else
       {
          if (bitmap.LoadFile("bitmaps/backgnd2.bmp", wxBITMAP_TYPE_BMP))
             dc.DrawBitmap(bitmap, 0, 0);
       }
    }


    int vertice_index;
    for (vertice_index=0; vertice_index <= 80; vertice_index+=4)
    {
        if ((frame->Ritorna_millisec_indice() -1) == (vertice_index / 4) )
           dc.SetPen(wxPen(wxT("yellow"), 2, wxSOLID));
        else
        {
           dc.SetPen(wxPen(wxT("gray"),  2, wxSOLID));
           if (frame->Ritorna_NumeroDownloads() > 21  && frame->MostraColoreIstogramma())
              if (frame->millisec_serie[((vertice_index+1) / 4)] < frame->Ritorna_media_totale() * 0.80 )
                 dc.SetPen(wxPen(wxT("green"),  2, wxSOLID));
              else
              if (frame->millisec_serie[((vertice_index+1) / 4)] > frame->Ritorna_media_totale() * 1.10 )
                 dc.SetPen(wxPen(wxT("red"),    2, wxSOLID));
        }
        vertice[vertice_index+0]= wxPoint(vertice_index+0+TAB_H, TAB_V -   2);
        vertice[vertice_index+1]= wxPoint(vertice_index+0+TAB_H, TAB_V - ((int) frame->millisec_serie[((vertice_index+1) / 4)] / frame->Ritorna_riduzione_istogramma() ));
        if ( ((int) frame->millisec_serie[((vertice_index+1) / 4)] / 55) > 1 )
           dc.DrawLine(vertice[vertice_index+0], vertice[vertice_index+1]);
    }

}



void Istogramma::OnPaint()
{
    DisegnaIstogramma();
}




// --------------------------------------------------------------------------
// MyFrame
// --------------------------------------------------------------------------

MyFrame::MyFrame() : wxFrame((wxFrame *)NULL, -1,
                             _("Connection Alive  1.6"),
                             wxDefaultPosition, wxSize(550, 350), wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION)
{

  wxMenuItem *pItem;

  wxBitmap bmpSlider       (_T("slider"      ));
  wxBitmap bmpAvviaPing    (_T("avviaping"   ));
  wxBitmap bmpBloccaPing   (_T("bloccaping"  ));
  wxBitmap bmpBloccaPing_d (_T("bloccaping_d"));
  wxBitmap bmpOpzioni      (_T("opzioni"     ));
  wxBitmap bmpEsci         (_T("esci"        ));
  wxBitmap bmpGrigio       (_T("grigio"      ));
  wxBitmap bmpLog          (_T("log"         ));
  wxBitmap bmpCache        (_T("cache"       ));
  wxBitmap bmpAutore       (_T("autore"      ));
  wxBitmap bmpstatistiche  (_T("statistiche" ));


  wxBitmap bmpMinimizza    (_T("minimizza"   ));
  wxBitmap bmpDock         (_T("dock"        ));
  wxBitmap bmpCalcolatrice (_T("calcolatrice"));
  wxBitmap bmpConnessioni  (_T("connessioni" ));
  wxBitmap bmpStato        (_T("stato"       ));
  wxBitmap bmpSorgenti     (_T("sorgenti"    ));
  wxBitmap bmpOrologio     (_T("orologio"    ));



  SetIcon(wxICON(mondrian));

  m_menuFile = new wxMenu();
  m_SubMenu  = new wxMenu();

  pItem = new wxMenuItem(m_menuFile,
  CLIENT_SCEGLILOGFILE,
  _T("Salva  Sessione"),
  _("Salva la sessione di lavoro su un File"));
  pItem->SetBitmaps(bmpLog);
  m_SubMenu->Append(pItem);


  pItem = new wxMenuItem(m_menuFile,
  CLIENT_PULISCILOGFILE,
  _T("Pulisci Sessione"),
  _("Pulisce la sessione di lavoro a video"));
  pItem->SetBitmaps(bmpGrigio);
  m_SubMenu->Append(pItem);


  pItem = new wxMenuItem(m_menuFile,
  CLIENT_ULTIMOLOG,
  _T("Edita Sessione precedente"),
  _("Edita su notepad l'ultima sessione di lavoro salvata"));
  pItem->SetBitmaps(bmpGrigio);
  m_SubMenu->Append(pItem);


  pItem = new wxMenuItem(m_menuFile, ID_SUB_MENU, _T("&Sessione"), _T(""),  wxITEM_CHECK, m_SubMenu);
  pItem->SetBitmaps(bmpGrigio);
  m_menuFile->Append(pItem);

  m_menuFile->AppendSeparator();

  pItem = new wxMenuItem(m_menuFile,
  CLIENT_NASCONDIFRAME,
  _T("Minimizza nella Taskbar\tAlt-M"),
  _("Nasconde Connection Alive nella Taskbar"));
  pItem->SetBitmaps(bmpMinimizza);
  m_menuFile->Append(pItem);

  Menu1 = new wxMenuItem(m_menuFile,
  AGGANCIA_TELECOMANDO,
  _T("Aggancia il Telecomando"),
  _("Sposta il telcomando nella parte inferiore destra dello schermo"));
  Menu1->SetBitmaps(bmpDock);
  m_menuFile->Append(Menu1);


  m_menuFile->Append(NASCONDI_TELECOMANDO, _T("   Mostra Telecomando"), _T("Mostra/Nasconde il Telecomando"), TRUE);
  m_menuFile->Check(NASCONDI_TELECOMANDO, TRUE);

  m_menuFile->Append(MOSTRA_ISTOGRAMMA, _T("   Mostra  Istogramma"), _T("Mostra/Nasconde il grafico dei download"), TRUE);
  m_menuFile->Check(MOSTRA_ISTOGRAMMA, FALSE);

  m_menuFile->AppendSeparator();

  pItem = new wxMenuItem(m_menuFile,
  CLIENT_QUIT,
  _T("Esci\tAlt-X"),
  _("Esci dal Programma"));
  pItem->SetBitmaps(bmpEsci);
  m_menuFile->Append(pItem);


  m_menuEdit = new wxMenu();

  pItem = new wxMenuItem(m_menuEdit,
  WIZARD_RUN,
  _T("Wizard                           "),
  _("Attiva la configurazione automatica"));
  pItem->SetBitmaps(bmpGrigio);
  m_menuEdit->Append(pItem);

  pItem = new wxMenuItem(m_menuEdit,
  CLIENT_OPZIONI,
  _T("Opzioni"),
  _("Scegli le opzioni"));
  pItem->SetBitmaps(bmpOpzioni);
  m_menuEdit->Append(pItem);

  m_menuEdit->AppendSeparator();

  m_menuEdit->Append(CLIENT_COMMUTA_TOOLBAR, _T("   Mostra Toolbar Estesa\tAlt-T")  , _T("Abilita o Disabilita le icone supplementari"), TRUE);
  m_menuEdit->Check(CLIENT_COMMUTA_TOOLBAR, FALSE);

  m_menuEdit->Append(CLIENT_COMMUTA_BELL,    _T("   Click dopo  Download\tAlt-C"), _T("Abilita o Disabilita il Beep sul download"), TRUE);
  m_menuEdit->Check(CLIENT_COMMUTA_BELL, FALSE);

  m_menuEdit->AppendSeparator();

  pItem = new wxMenuItem(m_menuEdit,
  CLIENT_LANCIACALCOLATRICE,
  _T("Calcolatrice"),
  _("Lancia la Calcolatrice"));
  pItem->SetBitmaps(bmpCalcolatrice);
  m_menuEdit->Append(pItem);



  m_menuConnessione = new wxMenu();

  Menu2 = new wxMenuItem(m_menuConnessione,
  CLIENT_PING,
  _T("Avvia   Download\tAlt-A"),
  _("Avvia il loop sull'indirizzo scelto"));
  Menu2->Enable(TRUE);
  Menu2->SetBitmaps(bmpAvviaPing);
  m_menuConnessione->Append(Menu2);

  Menu3 = new wxMenuItem(m_menuConnessione,
  CLIENT_CLOSE,
  _T("Blocca Download\tAlt-B"),
  _("Chiudi la sessione di rete"));
  Menu3->Enable(FALSE);
  Menu3->SetBitmaps(bmpBloccaPing_d);
  m_menuConnessione->Append(Menu3);

  m_menuConnessione->AppendSeparator();

  pItem = new wxMenuItem(m_menuConnessione,
  CLIENT_RITARDO,
  _T("Intervallo Download"),
  _("Regola l'intervallo tra due Download"));
  pItem->SetBitmaps(bmpOrologio);
  m_menuConnessione->Append(pItem);


  pItem = new wxMenuItem(m_menuConnessione,
  CLIENT_TIMEOUT,
  _T("Timeout Ping"),
  _T("Regola il Timeout del comando Ping"));
  pItem->SetBitmaps(bmpOrologio);
  m_menuConnessione->Append(pItem);


  m_menuConnessione->AppendSeparator();


  pItem = new wxMenuItem(m_menuConnessione,
  CLIENT_ELENCAISP,
  _T("Connessioni Disponibili"),
  _("Elenca le connessioni disponibili sul sistema"));
  pItem->SetBitmaps(bmpGrigio);
  m_menuConnessione->Append(pItem);

  pItem = new wxMenuItem(m_menuConnessione,
  CLIENT_DIAL,
  _T("Vai su Internet"),
  _("Attiva la Connessione di Accesso Remoto per la rete"));
  pItem->SetBitmaps(bmpGrigio);
  m_menuConnessione->Append(pItem);

  pItem = new wxMenuItem(m_menuConnessione,
  CONTROLLA_CONNESSIONE,
  _T("Stato Connessione"),
  _("Controlla lo stato della Connessione"));
  pItem->SetBitmaps(bmpGrigio);
  m_menuConnessione->Append(pItem);



  m_menuInfo = new wxMenu();

  pItem = new wxMenuItem(m_menuInfo,
  CLIENT_INDEX,
  _T("Cache"),
  _("Mostra la Pagina scaricata"));
  pItem->SetBitmaps(bmpCache);
  m_menuInfo->Append(pItem);

  m_menuInfo->AppendSeparator();

  pItem = new wxMenuItem(m_menuInfo,
  CLIENT_SORGENTI,
  _T("Sorgenti"),
  _("Sorgenti originali di Connection Alive rel 1.6"));
  pItem->SetBitmaps(bmpSorgenti);
  m_menuInfo->Append(pItem);


  pItem = new wxMenuItem(m_menuInfo,
  CLIENT_RINGRAZIAMENTI,
  _T("Ringraziamenti"),
  _("Risorse utilizzate per lo sviluppo di questo software"));
  pItem->SetBitmaps(bmpGrigio);
  m_menuInfo->Append(pItem);

  m_menuInfo->AppendSeparator();

  pItem = new wxMenuItem(m_menuInfo,
  CLIENT_ABOUT,
  _T("Autore"),
  _("Mostra Info Box"));
  pItem->SetBitmaps(bmpAutore);
  m_menuInfo->Append(pItem);





  m_menuBar = new wxMenuBar();
  m_menuBar->Append(m_menuFile,        _("&File"));
  m_menuBar->Append(m_menuEdit,        _("&Edit"));
  m_menuBar->Append(m_menuConnessione, _("&Connessione"));
  m_menuBar->Append(m_menuInfo,        _("&Info"));

  SetMenuBar(m_menuBar);

  CreateStatusBar(2);

  toolBar = CreateToolBar();
  toolBar->SetToolBitmapSize(wxSize(48, 48));
  toolBar->SetMargins(8, 8);
  wxBitmap bmpAvviaPing_b  (_T("avviaping_b" ));
  wxBitmap bmpBloccaPing_b (_T("bloccaping_b"));
  toolBar->AddSeparator();
  ADD_TOOL(CLIENT_PING   ,       bmpAvviaPing_b , _("Avvia")   , _("Avvia  Download"));
  ADD_TOOL(CLIENT_CLOSE  ,       bmpBloccaPing_b, _("Blocca")  , _("Blocca Download"));
  toolBar->AddSeparator();
  toolBar->Realize();




  m_text        =  new wxTextCtrl(this, -1,
                   _(" [ Integra di Sebastiano Dimartina ]         Connection Alive rel 1.6.1     (11/2004)\n\n\n Per configurare in modo guidato il programma vai su  (Menu->Edit->Wizard)\n\n Per iniziare il download sul sito prescelto  vai su         (Menu->Connessione->Avvia Download)\n\n\n Ok...\n"),
                   wxDefaultPosition, wxDefaultSize,
                   wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH );


  m_sock = new wxSocketClient();

  m_sock->SetEventHandler(*this, SOCKET_ID);
  m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
                    wxSOCKET_INPUT_FLAG |
                    wxSOCKET_LOST_FLAG);
  m_sock->Notify(TRUE);

  m_PingLoop    = FALSE;
  m_Carico_Ping = 32;
  m_Timeout     = 2;


  long appoggio;
  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetPath(_T("/Controls"));
  pConfig->Read(_T("Slider1"), &appoggio);
  m_SecRitardo  = appoggio;

  m_telecomando = new Telecomando(this);
  m_dial        = wxDialUpManager::Create();

  s_abilitato   = FALSE;
  t_abilitato   = TRUE;
  c_abilitato   = TRUE;
  i_abilitato   = FALSE;

  h_abilitato   = TRUE;

  b_abilitato   = FALSE;
  p_abilitato   = TRUE;
  Coordinate    = TRUE;

}



MyFrame::~MyFrame()
{

  delete m_sock;

}



void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetPath(_T("/Controls"));

  if (wxT(pConfig->Read(_T("Radio1"), _T("")))  == "Salva Sessione All'uscita")
  {
     wxString f = wxFileSelector( wxT("Salvataggio Sessione automatico"), (const wxChar *)NULL,
                               wxT(pConfig->Read(_T("Text1"), _T(""))),
                               wxT("txt"), wxT("TXT files (*.txt)|*.txt"), wxSAVE | wxOVERWRITE_PROMPT  );
     if (f == _T(""))  return;

     m_text->SaveFile(f);
  }

  ChiudiTCP();
  Close(TRUE);

}



void MyFrame::SalvaCoord()
{

int             larghezza_prec,
                altezza_prec,
                x_prec,
                y_prec;

  if (Coordinate)
  {
     frame->GetSize(&larghezza_prec, &altezza_prec);
     frame->GetPosition(&x_prec, &y_prec);
     frame->Maximize();
     frame->GetSize(&larghezza_win, &altezza_win);
     frame->SetSize(x_prec, y_prec, larghezza_prec, altezza_prec);
     Coordinate = FALSE;
  }

}



void MyFrame::NascondiFrame(wxCommandEvent& WXUNUSED(event))
{

  SalvaCoord();
  m_telecomando->Move(larghezza_win -94, altezza_win -110);
  frame->Show(FALSE);

}



void MyFrame::ControllaConnessione(wxCommandEvent& WXUNUSED(event))
{
   if(m_dial->IsOnline())
    {
        m_text->SetDefaultStyle(wxTextAttr(*wxBLUE));
        m_text->AppendText(_("\n\n Connesso alla Rete\n\n"));
        m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
    }
   else
    {
        m_text->SetDefaultStyle(wxTextAttr(*wxRED));
        m_text->AppendText(_("\n\n Disconnesso\n\n\n"));
        m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
    }
}



void MyFrame::Dial(wxCommandEvent& WXUNUSED(event))
{

    wxYield();
    wxBeginBusyCursor();

    if (m_dial->Dial())
    {
        m_text->SetDefaultStyle(wxTextAttr(*wxBLUE));
        m_text->AppendText(_("\n\n In Connessione...\n"));
    }
    else
    {
        m_text->SetDefaultStyle(wxTextAttr(*wxRED));
        m_text->AppendText(_("\n\n Nessuna Connessione\n"));
    }

    m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
    wxEndBusyCursor();
}



void MyFrame::ElencaIsp(wxCommandEvent& WXUNUSED(event))
{

    wxArrayString names;
    size_t nCount = m_dial->GetISPNames(names);
    if ( nCount == 0 )
    {
        m_text->SetDefaultStyle(wxTextAttr(*wxRED));
        m_text->AppendText(_("\n\n Nessuna Connessione...\n\n"));
        m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
    }
    else
    {
        wxString msg = _T("\n Connessioni Disponibili:   ");
        for ( size_t n = 0; n < nCount; n++ )
        {
            msg << "\"" << names[n] << "\";  ";
        }
        m_text->SetDefaultStyle(wxTextAttr(*wxBLUE));
        m_text->AppendText(_(msg));
        m_text->AppendText(_("\n\n"));
        m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
    }
}




void MyFrame::AgganciaTelecomando(wxCommandEvent& WXUNUSED(event))
{

  SalvaCoord();
  m_telecomando->Move(larghezza_win -94, altezza_win -110);

}



void MyFrame::NascondiTelecomando(wxCommandEvent& WXUNUSED(event))
{

  wxBitmap bmpGrigio       (_T("grigio"      ));
  wxBitmap bmpDock         (_T("dock"        ));

  t_abilitato = !t_abilitato;

  if (t_abilitato == FALSE)
  {
    m_telecomando->Show(FALSE);
    Menu1->Enable(FALSE);
    Menu1->SetBitmaps(bmpGrigio);
  }
  else
  {
    m_telecomando->Show(TRUE);
    Menu1->Enable(TRUE);
    Menu1->SetBitmaps(bmpDock);
  }

}



void MyFrame::VisualizzaIstogramma(wxCommandEvent& WXUNUSED(event))
{

  i_abilitato = !i_abilitato;

  if (h_abilitato)
     VisualizzaHelpIstogramma();

  if (i_abilitato == FALSE)
     mini_frame->Show(FALSE);
  else
     mini_frame->Show(TRUE);


}





void MyFrame::CommutaBell(wxCommandEvent& WXUNUSED(event))
{

  b_abilitato = !b_abilitato;

}



void MyFrame::CommutaBMP(wxCommandEvent& WXUNUSED(event))
{

  p_abilitato = !p_abilitato;
  mini_frame->Show(FALSE);
  mini_frame->Show(TRUE);

}



void MyFrame::CommutaColore(wxCommandEvent& WXUNUSED(event))
{

  c_abilitato = !c_abilitato;
  mini_frame->Show(FALSE);
  mini_frame->Show(TRUE);

}



void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{

        wxBoxSizer *topsizer;
        wxHtmlWindow *html;
        wxDialog dlg(this, -1, wxString(_("")));
        dlg.Centre(wxVERTICAL);

        topsizer = new wxBoxSizer(wxVERTICAL);

        html = new wxHtmlWindow(&dlg, -1, wxPoint(20, 20), wxSize(480, 175), wxHW_SCROLLBAR_NEVER);
        html -> SetBorders(1);
        html -> LoadPage(wxT("ABOUT.HTML"));
        html -> SetSize(html -> GetInternalRepresentation() -> GetWidth(),
                        html -> GetInternalRepresentation() -> GetHeight());

        topsizer -> Add(html, 1, wxALL, 10);
        topsizer -> Add(new wxStaticLine(&dlg, -1), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

        wxButton *bu1 = new wxButton(&dlg, wxID_OK, _("OK"));
        bu1 -> SetDefault();

        topsizer -> Add(bu1, 0, wxALL | wxALIGN_RIGHT, 15);

        dlg.SetAutoLayout(TRUE);
        dlg.SetSizer(topsizer);
        topsizer -> Fit(&dlg);

        dlg.CentreOnParent();
        dlg.ShowModal();

}



void MyFrame::NascondiToolbar()
{

    toolBar->RemoveTool(CLIENT_OPZIONI);
    toolBar->RemoveTool(CLIENT_COMMUTA_PING);
    toolBar->RemoveTool(CLIENT_RITARDO);
    toolBar->RemoveTool(CLIENT_INDEX);
    toolBar->Realize();

}



void MyFrame::VisualizzaHelpIstogramma()
{


  m_text->AppendText(_("\n"));
  m_text->AppendText(_("\n Il grafico dell'istogramma visualizza i tempi di risposta\n"));
  m_text->AppendText(_("\n del sito e della connessione negli ultimi 20 download. \n\n"));
  m_text->AppendText(_("\n Altezze e colori delle barre ("));
     m_text->SetDefaultStyle(wxTextAttr(*wxRED));
  m_text->AppendText(_("Rosso"));
     m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
  m_text->AppendText(_(" = Lento, "));
     m_text->SetDefaultStyle(wxTextAttr(*wxGREEN));
  m_text->AppendText(_("Verde"));
     m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
  m_text->AppendText(_(" = Veloce, Grigio = nella media)\n"));
  m_text->AppendText(_("\n vengono calibrati solo dopo la sequenza di test dei primi 20 download.\n"));
  m_text->AppendText(_("\n"));
  h_abilitato = FALSE;

}






void MyFrame::MostraToolbar()
{

    wxBitmap bmpOpzioni_b    (_T("opzioni_b"   ));
    wxBitmap bmpCommuta_b    (_T("commuta_b"   ));
    wxBitmap bmpTaskbar_b    (_T("taskbar_b"   ));
    wxBitmap bmpLog_b        (_T("log_b"       ));
    wxBitmap bmpGrigio_b     (_T("grigio_b"    ));


    ADD_TOOL(CLIENT_OPZIONI,       bmpOpzioni_b   , _("Opzioni")         , _("Configura Connection Alive"));
    ADD_TOOL(CLIENT_COMMUTA_PING,  bmpCommuta_b   , _("Commuta Ping")    , _("Attiva / Disattiva Ping"));
    ADD_TOOL(CLIENT_RITARDO,       bmpGrigio_b    , _("Ritardo Download"), _("Regola l'intervallo tra due Downloads"));
    ADD_TOOL(CLIENT_INDEX,         bmpTaskbar_b   , _("Cache")           , _("Mostra la Pagina scaricata"));


    toolBar->Realize();

}



void MyFrame::OnCommutaToolbar(wxCommandEvent& WXUNUSED(event))
{

    s_abilitato = !s_abilitato;

    if (s_abilitato == FALSE)
       NascondiToolbar();
    else
       MostraToolbar();

}



void MyFrame::OnRingraziamenti(wxCommandEvent& WXUNUSED(event))
{

   wxMessageBox("\n Connection Alive e' stato scritto usando:\n Compilatore C++ Mingw Rel 3.2  (www.mingw.org),    \n GUI Framework WxWidgets (www.wxwidgets.org).    \n\n Connection Alive e' basato sui lavori di:\n Vaclav Slavik,\n Guillermo Rodriguez Garcia,\n Vadim Zeitlin,\n Julian Smart.\n\n Utilizzo su Intranet garantito solo con Apache >1.3\n\n Suggerimenti e bugs vanno inviati alla mia email:\n          <connectionalive@softhome.net>\n", _T("Ringraziamenti"),  wxOK | wxICON_INFORMATION, this);

}



void MyFrame::OnSorgenti(wxCommandEvent& WXUNUSED(event))
{

   wxMessageBox("I sorgenti di  Connection Alive 1.6  sono disponibili solo su richiesta\ninviando una email  all'indirizzo: <connectionalive@softhome.net>.", _T("Sorgenti"),  wxOK | wxICON_INFORMATION, this);

}



void MyFrame::UltimoLog(wxCommandEvent& WXUNUSED(event))
{

   wxString appoggio;

   wxConfigBase *pConfig = wxConfigBase::Get();
   pConfig->SetPath(_T("/Controls"));
   appoggio.Append(_("notepad "));

  wxString f = wxFileSelector( wxT("Carica file di Sessione"), (const wxChar *)NULL,
                               wxT(pConfig->Read(_T("Text1"), _T(""))),
                               wxT("txt"), wxT("TXT files (*.txt)|*.txt"), wxOPEN );

   if (f.Len() > 0)
   {
      appoggio.Append(f);
      wxExecute(appoggio, wxEXEC_ASYNC);
   }

}



void MyFrame::OnIndex(wxCommandEvent& WXUNUSED(event))
{

        wxBoxSizer *topsizer;
        wxHtmlWindow *html;
        wxDialog dlg(this, -1, wxString(_("")));
        dlg.Centre(wxVERTICAL);

        topsizer = new wxBoxSizer(wxVERTICAL);

        html = new wxHtmlWindow(&dlg, -1, wxDefaultPosition, wxSize(480, 180), wxHW_SCROLLBAR_AUTO);
        html -> SetBorders(0);
        html -> LoadPage(wxT("INDEX.HTML"));
        html -> SetSize(html -> GetInternalRepresentation() -> GetWidth(),
                        html -> GetInternalRepresentation() -> GetHeight());

        topsizer -> Add(html, 1, wxALL, 10);
        topsizer -> Add(new wxStaticLine(&dlg, -1), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

        wxButton *bu1 = new wxButton(&dlg, wxID_OK, _("OK"));
        bu1 -> SetDefault();

        topsizer -> Add(bu1, 0, wxALL | wxALIGN_RIGHT, 15);

        dlg.SetAutoLayout(TRUE);
        dlg.SetSizer(topsizer);
        topsizer -> Fit(&dlg);
        dlg.CentreOnParent();
        dlg.ShowModal();

}



void MyFrame::OnRitardo(wxCommandEvent& WXUNUSED(event))
{

    long appoggio;

    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Controls"));
    pConfig->Read(_T("Slider1"), &appoggio);

    m_SecRitardo = appoggio;
    long res = wxGetNumberFromUser( _T(" Introduci l'intervallo in secondi\n")
                                    _T(" tra due Downloads"),
                                    _T("Introduci un Numero:"), _T(""),
                                     m_SecRitardo, 0, 100, this );
   ScriviRitardo(res);
}



void MyFrame::OnTimeout(wxCommandEvent& WXUNUSED(event))
{

    long res = wxGetNumberFromUser( _T(" Introduci il Timeout in secondi\n")
                                    _T(" per ogni risposta del comando Ping\n (opzione \"-w timeout value\")"),
                                    _T("Introduci un Numero:"), _T(""),
                                     m_Timeout, 0, 8, this );
   ScriviTimeout(res);

}



void MyFrame::MostraFrame(wxCommandEvent& WXUNUSED(event))
{

  frame->Show(TRUE);
  frame->SetFocus();

}



void MyFrame::OnOpzioni(wxCommandEvent& WXUNUSED(event))
{

    wxDialog dialog( this, -1, wxString(_T(""))  );
    dialog.Centre(wxVERTICAL);

    wxBoxSizer *topsizer = new wxBoxSizer( wxHORIZONTAL );

    wxNotebook *notebook = new wxNotebook( &dialog, -1 );
    wxNotebookSizer *nbs = new wxNotebookSizer( notebook );
    topsizer->Add( nbs, 1, wxGROW );



    wxPanel *panel = new wxPanel( notebook, -1 );
    notebook->AddPage( panel, _T("Configurazione") );


    wxSizer *panelsizer = new wxBoxSizer( wxVERTICAL );
    wxSizer *appoggiosizer = new wxBoxSizer( wxVERTICAL );


    wxStaticText *text1 =   new wxStaticText(&dialog, -1, _T("   "), wxDefaultPosition, wxSize(250,55));
    appoggiosizer->Add(text1, 0, wxALIGN_RIGHT | wxALL, 0 );


    Master_chk1 = new wxCheckBox(&dialog, -1, _T("Usa Protocollo ICMP \"Ping\" sul server"), wxPoint(0,0), wxSize(210,-1));
    appoggiosizer->Add(Master_chk1, 0, wxALIGN_CENTER | wxALL, 4);

    Master_chk2 = new wxCheckBox(&dialog, -1, _T("Mostra la RAM disponibile sul Sistema"), wxPoint(0,0), wxSize(210,-1));
    appoggiosizer->Add(Master_chk2, 0, wxALIGN_CENTER | wxALL, 4);

    Master_chk3 = new wxCheckBox(&dialog, -1, _T("Download  sulla  rete Intranet  privata"),wxPoint(0,0), wxSize(210,-1));
    appoggiosizer->Add(Master_chk3, 0, wxALIGN_CENTER | wxALL, 4);




    static const wxString modes[] =
    {
        _T("Sessione di tipo analitico"),
        _T("Non mostrare il dettaglio dei singoli Downloads"),
    };


    Master_radio1  = new wxRadioBox (&dialog, -1, _T(""),  wxDefaultPosition, wxSize(260,-1),  WXSIZEOF(modes), modes,  1, wxRA_SPECIFY_COLS);
    appoggiosizer->Add(Master_radio1, 0, wxALIGN_CENTER | wxALL, 9);


    wxButton *button1=     new  MyButton(&dialog, CLIENT_SALVAOPZIONIMASTER, _T("Applica"),wxDefaultPosition, wxSize(90,25));
    appoggiosizer->Add(button1,  0, wxALIGN_RIGHT | wxLEFT|wxRIGHT|wxBOTTOM, 6 );

    wxButton *button2 =    new  MyButton(&dialog, wxID_OK, _T("Esci"),wxDefaultPosition, wxSize(90,25));
    appoggiosizer->Add(button2,  0, wxALIGN_RIGHT | wxLEFT|wxRIGHT|wxBOTTOM, 6 );

    wxStaticText *text2 =   new wxStaticText(&dialog, -1, _T("   "), wxDefaultPosition, wxSize(250,2) );
    appoggiosizer->Add(text2, 0, wxALIGN_RIGHT | wxLEFT|wxRIGHT|wxBOTTOM, 0);




    wxBitmap bitmap(0, 0);

    bitmap = wxBitmap(_T("bitmaps/barra.bmp"), wxBITMAP_TYPE_BMP);
    new wxStaticBitmap (&dialog, -1, bitmap, wxPoint(288, 20));


    bitmap = wxBitmap(_T("bitmaps/taskbar.bmp"), wxBITMAP_TYPE_BMP);
    new wxStaticBitmap (&dialog, -1, bitmap, wxPoint(5, 0));



    topsizer->Add(appoggiosizer, 1, wxGROW );


    wxStaticText *text3 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,10) );
    panelsizer->Add(text3, 0, wxGROW|wxALL, 0 );

    wxStaticText *text4 = new wxStaticText( panel, -1, _T("   Sito Internet per Download"), wxDefaultPosition, wxSize(250,-1) );
    panelsizer->Add(text4, 0, wxGROW|wxALL, 1 );

    control1 = new wxTextCtrl( panel, -1, _T("http://www.sitoascelta.it"), wxDefaultPosition, wxSize(256,-1) );
    panelsizer->Add(control1, 0, wxALIGN_CENTER, 4 );


    wxStaticText *text5 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,4) );
    panelsizer->Add(text5, 0, wxGROW|wxALL, 0 );


    wxStaticText *text6 = new wxStaticText( panel, -1, _T("   Nodo Intranet per Download"), wxDefaultPosition, wxSize(250,-1) );
    panelsizer->Add(text6, 0, wxGROW|wxALL, 1 );

    control2 = new wxTextCtrl( panel, -1, _T("http://localhost"), wxDefaultPosition, wxSize(256,-1) );
    panelsizer->Add(control2, 0, wxALIGN_CENTER, 4 );

    wxStaticText *text7 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,11) );
    panelsizer->Add(text7, 0, wxGROW|wxALL, 0);


    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Controls"));
    control1->SetValue(pConfig->Read(_T("Text3"), _T("")));
    control2->SetValue(pConfig->Read(_T("Text4"), _T("")));
    Master_radio1->SetStringSelection(pConfig->Read(_T("Radio3"), _T("")));


    bool bool1;
    bool bool2;
    bool bool3;
    pConfig->SetPath(_T("/Controls"));
    pConfig->Read(_T("ChkMaster1"), &bool1);
    Master_chk1->SetValue(bool1);
    pConfig->Read(_T("ChkMaster2"), &bool2);
    Master_chk2->SetValue(bool2);
    pConfig->Read(_T("ChkMaster3"), &bool3);
    Master_chk3->SetValue(bool3);


    wxStaticText *text8 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,8) );
    panelsizer->Add(text8, 0, wxGROW|wxALL, 1);

    wxButton *button3 = new MyButton(panel, CLIENT_IDENTIFICAZIONE, _T("Identificazione"),wxDefaultPosition, wxSize(120,23) );
    panelsizer->Add(button3, 0, wxALIGN_LEFT | wxLEFT|wxRIGHT|wxBOTTOM, 6 );

    wxButton *button4 = new MyButton(panel, CLIENT_INTERVALLO, _T("Intervallo"),wxDefaultPosition, wxSize(120,23) );
    panelsizer->Add(button4, 0, wxALIGN_LEFT | wxLEFT|wxRIGHT|wxBOTTOM, 6 );

    wxButton *button5 = new MyButton(panel, CLIENT_LOGFILE, _T("Sessione"),wxDefaultPosition, wxSize(120,23) );
    panelsizer->Add(button5, 0, wxALIGN_LEFT | wxLEFT|wxRIGHT|wxBOTTOM, 6 );

    wxButton *button6 = new MyButton(panel, CLIENT_CONNESSIONE, _T("Connessione"),wxDefaultPosition, wxSize(120,23) );
    panelsizer->Add(button6, 0, wxALIGN_LEFT | wxLEFT|wxRIGHT|wxBOTTOM, 6 );


    panel->SetAutoLayout( TRUE );
    panel->SetSizer( panelsizer );
    dialog.SetAutoLayout( TRUE );
    dialog.SetSizer( topsizer );
    topsizer->Fit( &dialog );
    topsizer->SetSizeHints( &dialog );
    dialog.CentreOnScreen(wxBOTH);
    dialog.ShowModal();

}



void MyFrame::OnSalvaOpzioniMaster(wxCommandEvent& WXUNUSED(event))
{

  wxConfigBase *pConfig = wxConfigBase::Get();
  if ( pConfig == NULL )
     return;
  pConfig->Write(_T("/Controls/Text3")     , control1->GetValue().c_str());
  pConfig->Write(_T("/Controls/Text4")     , control2->GetValue().c_str());
  pConfig->Write(_T("/Controls/ChkMaster1"), Master_chk1->GetValue());
  pConfig->Write(_T("/Controls/ChkMaster2"), Master_chk2->GetValue());
  pConfig->Write(_T("/Controls/ChkMaster3"), Master_chk3->GetValue());
  pConfig->Write(_T("/Controls/Radio3")    , Master_radio1->GetStringSelection().c_str());

}



void MyFrame::OnSalvaOpzioniIdentita(wxCommandEvent& WXUNUSED(event))
{

  wxConfigBase *pConfig = wxConfigBase::Get();
  if ( pConfig == NULL )
     return;
  pConfig->Write(_T("/Controls/Radio2"), m_radioTextLines->GetStringSelection().c_str());

}



void MyFrame::OnSalvaOpzioniIntervallo(wxCommandEvent& WXUNUSED(event))
{


  wxConfigBase *pConfig = wxConfigBase::Get();
  if ( pConfig == NULL )
     return;
  pConfig->Write(_T("/Controls/Slider1"), (long) m_slider->GetValue() );

}



void MyFrame::OnSalvaOpzioniLogFile(wxCommandEvent& WXUNUSED(event))
{

  wxConfigBase *pConfig = wxConfigBase::Get();
  if ( pConfig == NULL )
     return;
  pConfig->Write(_T("/Controls/Text1"), nomelogfile->GetValue().c_str());
  pConfig->Write(_T("/Controls/Radio1"), m_radioTextLines->GetStringSelection().c_str());

}



void MyFrame::OnSalvaOpzioniConnessione(wxCommandEvent& WXUNUSED(event))
{

  wxConfigBase *pConfig = wxConfigBase::Get();
  if ( pConfig == NULL )
     return;
  pConfig->Write(_T("/Controls/Text2"), m_choice->GetStringSelection().c_str());
  pConfig->Write(_T("/Controls/ChkConnessione1") , Connect_chk1->GetValue());
  pConfig->Write(_T("/Controls/ChkConnessione2") , Connect_chk2->GetValue());

}



void MyFrame::OnIdentificazione(wxCommandEvent& WXUNUSED(event))
{


    wxDialog dialog( this, -1, wxString(_T(""))  );
    wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

    wxNotebook *notebook = new wxNotebook( &dialog, -1 );
    wxNotebookSizer *nbs = new wxNotebookSizer( notebook );
    topsizer->Add( nbs, 1, wxGROW );

    wxButton *button = new  MyButton(&dialog, CLIENT_SALVAOPZIONIIDENTITA, _T("Applica"),wxDefaultPosition, wxSize(90,25) );
    topsizer->Add(button,  0, wxALIGN_RIGHT | wxALL, 3 );

    wxButton *button9 = new wxButton(&dialog, wxID_OK, _T("Esci"),wxDefaultPosition, wxSize(90,25)  );
    topsizer->Add(button9, 0, wxALIGN_RIGHT | wxALL, 3 );

    wxPanel *panel = new wxPanel( notebook, -1 );
    notebook->AddPage( panel, _T("Identificazione") );

    wxSizer *panelsizer = new wxBoxSizer( wxVERTICAL );


    static const wxString modes[] =
    {
        _T("Identificati come MS Explorer"),
        _T("Identificati come Opera"),
        _T("Identificati come Mozilla"),
        _T("Identificati come Netscape"),
        _T("Identificati come Anonimo"),
    };


    m_radioTextLines  = new wxRadioBox (panel, -1, _T(""),  wxDefaultPosition, wxDefaultSize,  WXSIZEOF(modes), modes,  1, wxRA_SPECIFY_COLS);
    panelsizer->Add(m_radioTextLines, 0, wxALIGN_LEFT | wxALL, 9);


    wxStaticText *text1 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,3) );
    panelsizer->Add(text1, 0, wxGROW|wxALL, 0 );


    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Controls"));
    m_radioTextLines->SetStringSelection(pConfig->Read(_T("Radio2"), _T("")));


    panel->SetAutoLayout( TRUE );
    panel->SetSizer( panelsizer );
    dialog.SetAutoLayout( TRUE );
    dialog.SetSizer( topsizer );
    topsizer->Fit( &dialog );
    topsizer->SetSizeHints( &dialog );
    dialog.ShowModal();

}



void MyFrame::Onintervallo(wxCommandEvent& WXUNUSED(event))
{

    wxDialog dialog( this, -1, wxString(_T(""))  );

    wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

    wxNotebook *notebook = new wxNotebook( &dialog, -1 );
    wxNotebookSizer *nbs = new wxNotebookSizer( notebook );
    topsizer->Add( nbs, 1, wxGROW );


    wxButton *button = new  MyButton(&dialog, CLIENT_SALVAOPZIONIINTERVALLO, _T("Applica"),wxDefaultPosition, wxSize(90,25) );
    topsizer->Add(button, 0, wxALIGN_RIGHT | wxALL, 3 );

    wxButton *button9 = new wxButton(&dialog, wxID_OK, _T("Esci"),wxDefaultPosition, wxSize(90,25)  );
    topsizer->Add(button9, 0, wxALIGN_RIGHT | wxALL, 3 );


    wxPanel *panel = new wxPanel( notebook, -1 );
    notebook->AddPage( panel, _T("Secondi") );

    wxSizer *panelsizer = new wxBoxSizer( wxVERTICAL );

    wxStaticText *text1 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,3) );
    panelsizer->Add(text1, 5, wxGROW|wxALL, 0 );



    m_slider = new wxSlider( panel, 181, 0, 0, 100, wxPoint(18,90), wxSize(155,-1), wxSL_AUTOTICKS | wxSL_LABELS );
    m_slider->SetTickFreq(40, 0);
    panelsizer->Add(m_slider,    0, wxALIGN_LEFT | wxALL, 9);


    long appoggio;
    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Controls"));
    pConfig->Read(_T("Slider1"), &appoggio);
    m_slider->SetValue(appoggio);


    panel->SetAutoLayout( TRUE );
    panel->SetSizer( panelsizer );
    dialog.SetAutoLayout( TRUE );
    dialog.SetSizer( topsizer );
    topsizer->Fit( &dialog );
    topsizer->SetSizeHints( &dialog );
    dialog.ShowModal();

}



void MyFrame::OnLogFile(wxCommandEvent& WXUNUSED(event))
{


    wxDialog dialog( this, -1, wxString(_T(""))  );
    wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );
    wxNotebook *notebook = new wxNotebook( &dialog, -1 );
    wxNotebookSizer *nbs = new wxNotebookSizer( notebook );
    topsizer->Add( nbs, 1, wxGROW );


    wxButton *button1 = new   MyButton(&dialog, CLIENT_SALVAOPZIONILOGFILE, _T("Applica"),wxDefaultPosition, wxSize(90,25) );
    topsizer->Add(button1, 0, wxALIGN_RIGHT | wxALL, 3 );

    wxButton *button2 = new   MyButton(&dialog, wxID_OK, _T("Esci"),wxDefaultPosition, wxSize(90,25)  );
    topsizer->Add(button2, 0, wxALIGN_RIGHT | wxALL, 3 );


    wxPanel *panel = new wxPanel( notebook, -1 );
    notebook->AddPage( panel, _T("Sessione") );

    wxSizer *panelsizer = new wxBoxSizer( wxVERTICAL );


    static const wxString modes[] =
    {
        _T("Salva Sessione All'uscita"),
        _T("Salva Sessione Manualmente"),
    };


    m_radioTextLines  = new wxRadioBox (panel, -1, _T(""),  wxDefaultPosition, wxDefaultSize,  WXSIZEOF(modes), modes,  1, wxRA_SPECIFY_COLS);
    panelsizer->Add(m_radioTextLines, 0, wxALIGN_LEFT | wxALL, 9);


    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Controls"));
    m_radioTextLines->SetStringSelection(pConfig->Read(_T("Radio1"), _T("")));


    wxStaticText *text1 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,3) );
    panelsizer->Add(text1, 0, wxGROW|wxALL, 0 );


    wxStaticText *text2 = new wxStaticText( panel, -1, _T(" Nome del file di Sessione"), wxDefaultPosition, wxSize(250,-1) );
    panelsizer->Add(text2, 0, wxGROW|wxALL, 4 );

    nomelogfile = new wxTextCtrl( panel, -1, _T("..."), wxDefaultPosition, wxSize(250,-1) );
    panelsizer->Add(nomelogfile, 0, wxGROW|wxALL, 4 );


    wxStaticText *text3 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,3) );
    panelsizer->Add(text3, 0, wxGROW|wxALL, 0 );


    pConfig->SetPath(_T("/Controls"));
    nomelogfile->SetValue(pConfig->Read(_T("Text1"), _T("")));


    panel->SetAutoLayout( TRUE );
    panel->SetSizer( panelsizer );
    dialog.SetAutoLayout( TRUE );
    dialog.SetSizer( topsizer );
    topsizer->Fit( &dialog );
    topsizer->SetSizeHints( &dialog );
    dialog.ShowModal();

}



void MyFrame::OnConnessione(wxCommandEvent& WXUNUSED(event))
{


    wxDialog dialog( this, -1, wxString(_T(""))  );
    wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

    wxNotebook *notebook = new wxNotebook( &dialog, -1 );
    wxNotebookSizer *nbs = new wxNotebookSizer( notebook );
    topsizer->Add( nbs, 1, wxGROW );

    wxButton *button =  new  MyButton(&dialog, CLIENT_SALVAOPZIONICONNESSIONE, _T("Applica"),wxDefaultPosition, wxSize(90,25) );
    topsizer->Add(button, 0, wxALIGN_RIGHT | wxALL, 3 );

    wxButton *button9 = new wxButton(&dialog,  wxID_OK                       , _T("Esci"),   wxDefaultPosition, wxSize(90,25)  );
    topsizer->Add(button9, 0, wxALIGN_RIGHT | wxALL, 3 );


    wxPanel *panel = new wxPanel( notebook, -1 );
    notebook->AddPage( panel, _T("Connessione") );

    wxSizer *panelsizer = new wxBoxSizer( wxVERTICAL );



    wxStaticText *text1 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,3) );
    panelsizer->Add(text1, 5, wxGROW|wxALL, 0 );

    Connect_chk1 = new wxCheckBox(panel, -1, _T("Ignora pagine Java/Javascript"), wxPoint(0,0), wxSize(210,-1));
    panelsizer->Add(Connect_chk1, 0, wxALIGN_CENTER | wxALL, 4);

    Connect_chk2 = new wxCheckBox(panel, -1, _T("Ignora pagine ActiveX"), wxPoint(0,0), wxSize(210,-1));
    panelsizer->Add(Connect_chk2, 0, wxALIGN_CENTER | wxALL, 4);


    wxStaticText *text2 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,3) );
    panelsizer->Add(text2, 5, wxGROW|wxALL, 0 );


    wxString choices[] =
    {
        _T("Modem Analogico 14/56K"),
        _T("GPRS 4/8 Slots"),
        _T("ISDN 64/128K"),
        _T("UMTS"),
        _T("ADSL 640K/1.2M+"),
        _T("Altro")
    };


    m_choice = new wxChoice( panel, -1,  wxPoint(10,10), wxSize(120,70),5, choices, wxLB_NEEDED_SB );
    panelsizer->Add(m_choice, 0, wxGROW|wxALL, 4 );

    wxStaticText *text3 = new wxStaticText( panel, -1, _T("   "), wxDefaultPosition, wxSize(250,3) );
    panelsizer->Add(text3, 5, wxGROW|wxALL, 0 );


    bool bool1;
    bool bool2;
    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Controls"));
    m_choice->SetStringSelection(pConfig->Read(_T("Text2"), _T("")));
    pConfig->Read(_T("ChkConnessione1"), &bool1);
    Connect_chk1->SetValue(bool1);
    pConfig->Read(_T("ChkConnessione2"), &bool2);
    Connect_chk2->SetValue(bool2);


    panel->SetAutoLayout( TRUE );
    panel->SetSizer( panelsizer );
    dialog.SetAutoLayout( TRUE );
    dialog.SetSizer( topsizer );
    topsizer->Fit( &dialog );
    topsizer->SetSizeHints( &dialog );
    dialog.ShowModal();

}



void MyFrame::ChiudiTCP()
{

  if (m_PingLoop == TRUE)
  {
     wxBusyInfo info(_T("Sto completando il download..."), this);
     for ( int i = 0; i < 18; i++ )
        wxTheApp->Yield();
     wxSleep(1);
  }
  m_PingLoop = FALSE;
  m_sock->Close();

}



void MyFrame::OnCloseConnection(wxCommandEvent& WXUNUSED(event))
{

  wxString s;
  wxBitmap bmpAvviaPing    (_T("avviaping"   ));
  wxBitmap bmpBloccaPing_d (_T("bloccaping_d"));

  ChiudiTCP();

  m_text->AppendText(_("\n Download Bloccato...\n\n"));
  s.Printf(_(" \n Numero downloads: %ld \n\n"), ping_counter);
  m_text->AppendText(s);

  Menu2->SetBitmaps(bmpAvviaPing);
  Menu2->Enable(TRUE);
  Menu3->SetBitmaps(bmpBloccaPing_d);
  Menu3->Enable(FALSE);

}



void MyFrame::OnPing(wxCommandEvent& WXUNUSED(event))
{


  wxString s;
  wxString urlname;
  bool bool1;


  if (m_PingLoop == TRUE)
     return;


  wxBitmap bmpAvviaPing_d  (_T("avviaping_d" ));
  wxBitmap bmpBloccaPing   (_T("bloccaping"  ));

  Menu2->SetBitmaps(bmpAvviaPing_d);
  Menu2->Enable(FALSE);
  Menu3->SetBitmaps(bmpBloccaPing);
  Menu3->Enable(TRUE);

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetPath(_T("/Controls"));
  pConfig->Read(_T("ChkMaster3"), &bool1);

  m_text->AppendText(_("\n Test sulla Connessione...\n\n"));

  if ( bool1 != TRUE )
     urlname = wxGetTextFromUser(_("Introduci un Sito Internet valido"),
     _("Tipo Collegamento:Internet"),
     wxT(pConfig->Read(_T("Text3"), _T(""))));
  else
  if ( bool1 == TRUE )
     urlname = wxGetTextFromUser(_("Introduci un Nodo Intranet valido"),
     _("Tipo Collegamento:Intranet"),
     wxT(pConfig->Read(_T("Text4"), _T(""))));


  wxURL url(urlname);
  if (url.GetError() != wxURL_NOERR)
  {
    m_text->AppendText(_("\n Url Errato \n"));
    m_text->AppendText(_("\n Fine download \n"));
    return;
  }



  int  i;
  for (i=1; i <= 20; i++)
      millisec_serie[i] =0;
  millisec_indice =1;



  m_PingLoop = TRUE;
  ping_counter=0;
  millisecondi_complessivi =0.0;


  while (m_PingLoop == TRUE)
  {
    SetIcon(wxICON(connect));
    wxSafeYield();
    wxStartTimer();

    wxInputStream *data = url.GetInputStream();
    if (!data)
    {
      m_text->AppendText(_("\n Errore: non riesco a leggere dall' URL\n"));
      m_text->AppendText(_("\n Fine Test \n"));
      SetIcon(wxICON(mondrian));
      return;
    }


    ping_counter++;
    if (MostraRAM())
    {
       s.Printf(_(" Memoria libera: %4.1f Mbyte"), ((float) wxGetFreeMemory() / 1000000.0));
       SetStatusText(s, 0);
    }
    s.Printf(_(" Numero downloads: %ld "), ping_counter);
    SetStatusText(s, 1);
    wxSafeYield();

    wxFileOutputStream sout(wxT("INDEX.HTML") );
    if (!sout.Ok())
    {
      m_text->AppendText(_("\n Errore: non riesco ad aprire il file per l'output\n"));
      m_text->AppendText(_("\n Fine Test \n"));
      return;
      SetIcon(wxICON(mondrian));
    }


    data->Read(sout);
    millisecondi = wxGetElapsedTime();


    if (MostraPing())
       PingExec();

    if (b_abilitato)
       wxBell();


    s.Printf(_(" Pagina scaricata su    (Menu->Info->Cache)   in %4.0ld ms\n"), millisecondi);

    if (!LogAnalitico())
       m_text->AppendText(s);

    if (millisec_indice > 20)
        millisec_indice =1;
    millisec_serie[millisec_indice++] = millisecondi;
    millisecondi_complessivi += (float) millisecondi;


    SetIcon(wxICON(mondrian));
    delete data;
    wxSleep(m_SecRitardo);
    Statistiche();
  }

}



void MyFrame::OnScegliLogFile(wxCommandEvent& WXUNUSED(event))
{

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetPath(_T("/Controls"));

  wxString f = wxFileSelector( wxT("Salva Sessione"), (const wxChar *)NULL,
                               wxT(pConfig->Read(_T("Text1"), _T(""))),
                               wxT("txt"), wxT("TXT files (*.txt)|*.txt"), wxSAVE | wxOVERWRITE_PROMPT  );
  if (f == _T(""))  return;

  m_text->SaveFile(f);
  m_text->AppendText(_("\n Sessione salvata...\n\n"));

}



bool MyFrame::MostraRAM()
{

  bool bool2;

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetPath(_T("/Controls"));
  pConfig->Read(_T("ChkMaster2"), &bool2);
  return(bool2);

}



bool MyFrame::MostraBMPIstogramma()
{

  return(p_abilitato);

}



bool MyFrame::MostraColoreIstogramma()
{

  return(c_abilitato);

}



long MyFrame::Ritorna_millisec_indice()
{

  return(millisec_indice);

}



float MyFrame::Ritorna_media_totale()
{

  return(media_totale);

}


int MyFrame::Ritorna_riduzione_istogramma()
{

  float tmp = 1.0;
  float fattore_fisso     =   60;
  float media_riferimento = 1500;

  if (frame->Ritorna_NumeroDownloads() < 21)
     return((int) fattore_fisso);


  tmp = media_totale / media_riferimento;

  /*
  wxString s;
  s.Printf(_(" \n media_totale = : %f \n\n"), media_totale);
  m_text->AppendText(s);
  s.Printf(_(" \n media rif    = : %f \n\n"), media_riferimento);
  m_text->AppendText(s);
  s.Printf(_(" \n tmp          = : %f \n\n"), tmp);
  m_text->AppendText(s);
  s.Printf(_(" \n tmp * fatt fisso = : %f \n\n"), (tmp * fattore_fisso));
  m_text->AppendText(s);
  */

  return((int) (tmp * fattore_fisso));

}

  


long MyFrame::Ritorna_NumeroDownloads()
{

  return(ping_counter);

}



bool MyFrame::IdleLoop()
{

  return(m_PingLoop);

}



bool MyFrame::MostraPing()
{

  bool bool2;

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetPath(_T("/Controls"));
  pConfig->Read(_T("ChkMaster1"), &bool2);
  return(bool2);

}



bool MyFrame::LogAnalitico()
{

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetPath(_T("/Controls"));
  if (!strncmp("Non", (pConfig->Read(_T("Radio3"), _T(""))), 3))
     return(TRUE);
  else
     return(FALSE);
}



void MyFrame::Statistiche()
{

    wxString s;
    wxString titolo;
    int i;
    float somma=0;
    float media=0;
    float scostamento =0;


    for (i=1; i <= 20; i++)
    {

       if (millisec_serie[i] != 0)
          somma += (float) millisec_serie[i];
       else
          break;
    }
    --i;

    if (i)
       media = somma / i;
    else
       media = 0.0;

    media_totale = millisecondi_complessivi / (float) ping_counter;
    scostamento = 100.0 * (1.0 - (media / media_totale));


    titolo.Printf("    Statistiche");
    if (ping_counter > 20 )
    {
       if (scostamento > 0.0 )
       {
          s.Printf(_("\n Media ultimi %d Downloads = %4.0f ms.\n    In MIGLIORAMENTO  del %3.1f%% rispetto alla media complessiva (%4.0f ms)   \n\n"), i, media, scostamento, media_totale);
          titolo.Printf(_("Rialzo %3.1f%%"), scostamento);
       }
       else
       {
          s.Printf(_("\n Media ultimi %d Downloads = %4.0f ms.\n    In peggioramento  del %3.1f%% rispetto alla media complessiva (%4.0f ms)   \n\n"), i, media, scostamento, media_totale);
          titolo.Printf(_("Calo  %3.1f%%"), scostamento);
       }
    }
    else
       if (media != 0.0)
       {
          s.Printf(_("\n Media dei Downloads = %4.0f ms.\n\n"), media);
          titolo.Printf(_("Media %1.2f S"), media / 1000.0);
       }
       else
          s.Printf(_("\n Non e' stata ancora scaricata alcuna pagina...\n\n"));

    if (!LogAnalitico())
       m_text->AppendText(s);

    m_telecomando->SetTitle(titolo);
    m_telecomando->Layout();
    m_Istogramma->Refresh();

}



void MyFrame::Onstatistiche(wxCommandEvent& WXUNUSED(event))
{

   Statistiche();

}



void MyFrame::CommutaPing(wxCommandEvent& WXUNUSED(event))
{

  bool bool2;

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetPath(_T("/Controls"));

  pConfig->Read(_T("ChkMaster1"), &bool2);
  pConfig->Write(_T("/Controls/ChkMaster1"), !(bool2));

  if (!bool2)
  {
     m_text->SetDefaultStyle(wxTextAttr(*wxRED));
     m_text->AppendText("\n Ping Attivato\n\n\n");
     m_telecomando->SetTitle("Ping ON");
  }
  else
  {
     m_text->SetDefaultStyle(wxTextAttr(*wxBLUE));
     m_text->AppendText("\n Ping Disattivato\n\n\n");
     m_telecomando->SetTitle("Ping OFF");
  }

  m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
  m_telecomando->Layout();

}



void MyFrame::OnRunWizard(wxCommandEvent& WXUNUSED(event))
{
    wxWizard *wizard = new wxWizard(this, -1,
                    _T("Wizard di configurazione di Connection Alive"),
                    wxBITMAP(wiztest));

    wxWizardPageSimple *page1 = new wxWizardPageSimple(wizard);
    wxStaticText *text = new wxStaticText(page1, -1,
             _T("\n")
             _T(" Con il Wizard di Connection Alive potete impostare i parametri")
             _T("\n")
             _T(" di base per il funzionamento del programma.")
             _T("\n\n")
             _T(" Potete lanciare anche dopo il wizard da (Menu->Edit->Wizard)")
        );
    wxSize size = text->GetBestSize();


    PaginaWizard2    *page2 = new PaginaWizard2 (wizard);
    PaginaWizard4    *page4 = new PaginaWizard4 (wizard);
    PaginaWizard5    *page5 = new PaginaWizard5 (wizard);
    wxCheckboxPage   *page3 = new wxCheckboxPage (wizard, page2, page4);


    page1->SetNext(page2);
    page2->SetNext(page3);
    page4->SetNext(page5);

    wizard->SetPageSize(size);
    if ( wizard->RunWizard(page1) )
    {
        wxMessageBox(_T("Wizard completato con successo!"), _T(""),
                     wxICON_INFORMATION | wxOK);
    }

    wizard->Destroy();
}



void MyFrame::PulisciLogFile(wxCommandEvent& WXUNUSED(event))
{
    m_text->Clear();
}



void MyFrame::ScriviRitardo(long param)
{

    wxString msg;
    wxString t;

    int icon;
    if ( param < 0 )
    {
        msg = _T("\n Valore errato\n");
        icon = wxICON_HAND;
    }
    else
    {
        if (param == 1)
           msg.Printf(_T("\n Ritardo di un secondo\n\n"));
        if (param == 0)
        {
           msg.Printf(_T("\n Nessun ritardo  (0 secondi)\n\n"));
           m_text->SetDefaultStyle(wxTextAttr(*wxRED));
        }
        if (param != 1 && param !=0)
           msg.Printf(_T("\n Ritardo di %lu secondi\n\n"), param );

        t.Printf(_T("Ritardo= %lu sec."), param );
        icon = wxICON_INFORMATION;
    }
    m_SecRitardo = param;
    m_text->AppendText(msg);
    m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));

    m_telecomando->SetTitle(t);
    m_telecomando->Layout();

}



void MyFrame::ScriviTimeout(long param)
{

    wxString msg;

    int icon;
    if ( param < 0 )
    {
        msg = _T("\n Valore errato\n");
        icon = wxICON_HAND;
    }
    else
    {
        if (param == 1)
           msg.Printf(_T("\n Timeout Ping di un secondo\n\n"));
        if (param == 0)
           msg.Printf(_T("\n Timeout Ping di zero secondi\n\n"));
        if (param != 1 && param !=0)
           msg.Printf(_T("\n Timeout Ping di %lu secondi\n\n"), param );

        icon = wxICON_INFORMATION;
    }
    m_Timeout = param;
    m_text->AppendText(msg);

}



void MyFrame::AumentaRitardo(wxCommandEvent& WXUNUSED(event))
{
   m_SecRitardo++;
   ScriviRitardo(m_SecRitardo);
}



void MyFrame::DiminuisciRitardo(wxCommandEvent& WXUNUSED(event))
{
   if (m_SecRitardo > 0)
      m_SecRitardo--;
   else
      m_SecRitardo = 0;

   ScriviRitardo(m_SecRitardo);
}



void MyFrame::AumentaCaricoPing(wxCommandEvent& WXUNUSED(event))
{
   wxString s;
   wxString t;

   if (m_Carico_Ping < 30000)
      m_Carico_Ping *= 2;

   s.Printf( _("\n Carico ping = %ld bytes\n\n"), m_Carico_Ping);
   t.Printf(_("Ping di %ld b."), m_Carico_Ping);
   m_text->AppendText(s);

   m_telecomando->SetTitle(t);
   m_telecomando->Layout();

}



void MyFrame::DiminuisciCaricoPing(wxCommandEvent& WXUNUSED(event))
{
   wxString s;
   wxString t;

   if (m_Carico_Ping >= 64)
      m_Carico_Ping /= 2;

   s.Printf(_("\n Carico ping = %ld bytes\n\n"), m_Carico_Ping);
   t.Printf(_("Ping di %ld b."), m_Carico_Ping);
   m_text->AppendText(s);

   m_telecomando->SetTitle(t);
   m_telecomando->Layout();

}



void MyFrame::PingExec()
{

   bool bool1;
   wxString s;
   wxString appoggio;
   wxArrayString output, errors;

   wxConfigBase *pConfig = wxConfigBase::Get();
   pConfig->SetPath(_T("/Controls"));
   pConfig->Read(_T("ChkMaster3"), &bool1);

   s.Append(_("ping "));

   if ( bool1 == TRUE )
      appoggio.Append(pConfig->Read(_T("Text4"), _T("")));
   else
      appoggio.Append(pConfig->Read(_T("Text3"), _T("")));
   s.Append(appoggio.Mid(7, wxSTRING_MAXLEN));
   appoggio.Printf(_(" -n 1 -l %ld -w %ld"), m_Carico_Ping, m_Timeout * 1000);
   s.Append(appoggio);

   wxExecute(s, output, errors);
   frame->SetFocus();
   if (!LogAnalitico())
   {
      m_text->AppendText(_T("\n USER.ping.Exec() = \""));
      m_text->SetDefaultStyle(wxTextAttr(*wxRED));
      m_text->AppendText(output[2]);
      m_text->AppendText(_T("\"\n "));
      m_text->AppendText(output[6]);
      m_text->AppendText(_T("\n\n"));
      m_text->SetDefaultStyle(wxTextAttr(*wxBLACK));
   }

}



void MyFrame::LanciaCalcolatrice(wxCommandEvent& WXUNUSED(event))
{
    long m_pidLast;

    wxProcess *process = new wxProcess(this, "calc");
    m_pidLast = wxExecute("calc", wxEXEC_ASYNC, process);
    if (!m_pidLast)
    {
        wxMessageBox("Esecuzione di  \"Calcolatrice\"  Fallita! ", _T("Attenzione"),  wxICON_ERROR  | wxICON_INFORMATION, this);
        delete process;
    }
}



void MyFrame::OnSocketEvent(wxSocketEvent& event)
{
  wxString s = _("Evento Connessione: ");
  wxSocketBase *sock = event.GetSocket();

  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT : s.Append(_("wxSOCKET_INPUT\n")); break;
    case wxSOCKET_LOST  : s.Append(_("wxSOCKET_LOST\n")); break;
    default             : s.Append(_("Evento Inatteso!\n")); break;
  }

  m_text->AppendText(s);

  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT:
    {
      sock->SetNotify(wxSOCKET_LOST_FLAG);
      sock->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
      break;
    }
    case wxSOCKET_LOST:
    {

      m_text->AppendText(_("Chiusura socket.\n\n"));
      sock->Destroy();
      break;
    }
    default: ;
  }
}





// --------------------------------------------------------------------------
// Telecomando miniframe
// --------------------------------------------------------------------------

Telecomando::Telecomando(wxWindow *parent)
             : wxMiniFrame(parent, -1,
                           _("Telecomando"),
                           wxDefaultPosition,
                           wxDefaultSize,
                           wxCAPTION | wxSIMPLE_BORDER | wxSTAY_ON_TOP )
{
    wxPanel    *panel  = new wxPanel(this, -1);
    wxBoxSizer *sizer1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);

    wxBitmap
    bmpn = wxBITMAP(north),
    bmpw = wxBITMAP(west),
    bmpc = wxBITMAP(center),
    bmpe = wxBITMAP(east),
    bmps = wxBITMAP(south);

    bmpn.SetMask(new wxMask(bmpn, *wxLIGHT_GREY));
    bmpw.SetMask(new wxMask(bmpw, *wxLIGHT_GREY));
    bmpc.SetMask(new wxMask(bmpc, *wxLIGHT_GREY));
    bmpe.SetMask(new wxMask(bmpe, *wxLIGHT_GREY));
    bmps.SetMask(new wxMask(bmps, *wxLIGHT_GREY));

    wxBitmapButton
    *bn = new wxBitmapButton(panel, ID_NORTH,  bmpn),
    *bw = new wxBitmapButton(panel, ID_WEST ,  bmpw),
    *bc = new wxBitmapButton(panel, ID_CENTER, bmpc),
    *be = new wxBitmapButton(panel, ID_EAST ,  bmpe),
    *bs = new wxBitmapButton(panel, ID_SOUTH,  bmps);

#if wxUSE_TOOLTIPS
    bn->SetToolTip(_("Aumenta L'intervallo tra due Downloads"));
    bw->SetToolTip(_("Diminuisce il \"carico\" di Ping"));
    bc->SetToolTip(_("Attiva/Disattiva PING"));
    be->SetToolTip(_("Aumenta il \"carico\" di Ping"));
    bs->SetToolTip(_("Diminuisce L'intervallo tra due Downloads"));
#endif

    sizer2->Add( bw, 0, wxCENTRE | wxWEST,  4 );
    sizer2->Add( bc, 0, wxCENTRE);
    sizer2->Add( be, 0, wxCENTRE | wxEAST,  4 );
    sizer1->Add( bn, 0, wxCENTRE | wxNORTH, 4 );
    sizer1->Add( sizer2 );
    sizer1->Add( bs, 0, wxCENTRE | wxSOUTH, 4 );

    panel->SetSizer(sizer1);
    panel->SetAutoLayout(TRUE);
    sizer1->Fit(panel);
    SetClientSize(panel->GetSize());
    wxSize sz = GetSize();
    SetSizeHints(sz.x, sz.y, sz.x, sz.y);

    Move(20, 50);
    Show(TRUE);
}



void Telecomando::OnClose(wxCloseEvent& event)
{

    if (event.CanVeto())
        event.Veto();
    else
        Destroy();
}





// --------------------------------------------------------------------------
// MyTaskBarIcon
// --------------------------------------------------------------------------

void MyTaskBarIcon::OnMenuSetNewIcon(wxCommandEvent&)
{

  wxIcon icon(wxT("up"));
  if (!SetIcon(icon, wxT("Connection Alive")))
      wxMessageBox(wxT("Impossibile settare l'icona."));
}



void MyTaskBarIcon::OnRButtonUp(wxEvent&)
{

    wxMenu      menu;

    menu.Append(CLIENT_MOSTRAFRAME,   _T("Ripristina Connection Alive"));
    menu.Append(AGGANCIA_TELECOMANDO, _T("Aggancia il Telecomando"));
    menu.AppendSeparator();
    menu.Append(PU_OPZIONI,           _T("Opzioni"));
    menu.Append(CLIENT_INDEX,         _T("Cache"));
    menu.Append(PU_ABOUT,             _T("Autore"));
    PopupMenu(&menu);
}



void MyTaskBarIcon::OnLButtonDClick(wxEvent&)
{
    frame->Show(TRUE);
}



void MyTaskBarIcon::OnMenuExit(wxCommandEvent& )
{
    wxGetApp().ProcessIdle();
}



void MyTaskBarIcon::OnMouseMove(wxEvent&)
{
}

void MyTaskBarIcon::OnLButtonDown(wxEvent&)
{
}

void MyTaskBarIcon::OnLButtonUp(wxEvent&)
{
}

void MyTaskBarIcon::OnRButtonDown(wxEvent&)
{
}

void MyTaskBarIcon::OnRButtonDClick(wxEvent&)
{
}

void MyTaskBarIcon::OnMenuRestore(wxCommandEvent& )
{
}




// --------------------------------------------------------------------------
// CanvasParent
// --------------------------------------------------------------------------

BEGIN_EVENT_TABLE(CanvasParent, wxMiniFrame)
    EVT_CLOSE  (              CanvasParent::OnClose)
END_EVENT_TABLE()

CanvasParent::CanvasParent(wxWindow *parent, wxWindowID id, const wxString& title, const wxPoint& pos,
        const wxSize& size ) :
  wxMiniFrame(parent, id, title, pos, size, wxCAPTION | wxSIMPLE_BORDER | wxSTAY_ON_TOP)
{
    m_Istogramma = new Istogramma( this );
}



void CanvasParent::OnClose(wxCloseEvent& WXUNUSED(event))
{
  Destroy();
}

