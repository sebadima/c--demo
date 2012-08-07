/////////////////////////////////////////////////////////////////////////////
// Name:         myclasses.h
// Purpose:      File header di Connection Alive 1.5
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



class MyTaskBarIcon: public wxTaskBarIcon
{
public:
    MyTaskBarIcon() {};

    virtual void OnMouseMove(wxEvent&);
    virtual void OnLButtonDown(wxEvent&);
    virtual void OnLButtonUp(wxEvent&);
    virtual void OnRButtonDown(wxEvent&);
    virtual void OnRButtonUp(wxEvent&);
    virtual void OnLButtonDClick(wxEvent&);
    virtual void OnRButtonDClick(wxEvent&);

    void OnMenuRestore(wxCommandEvent&);
    void OnMenuExit(wxCommandEvent&);
    void OnMenuSetNewIcon(wxCommandEvent&);

DECLARE_EVENT_TABLE()
};



class MyButton : public wxButton
{
public:
    MyButton(wxWindow *parent,
             wxWindowID id,
             const wxString& label = wxEmptyString,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize)
        : wxButton(parent, id, label, pos, size)
    {
    }
private:
    DECLARE_EVENT_TABLE()
};




class PaginaWizard2 : public wxWizardPageSimple
{
public:

    PaginaWizard2(wxWizard *parent) : wxWizardPageSimple(parent)
    {

        (void)new wxStaticText(this, -1,
           _T(" Inserite l'indirizzo completo preceduto da http://")
           _T("\n")
           _T(" di un sito web a vostra scelta, es. un motore di ricerca."));
        m_ctrl = new wxTextCtrl( this, -1, _T("http://www.sitoascelta.it"), wxPoint(5, 50), wxSize(256,-1) );
    }


    void OnWizardCancel(wxWizardEvent& event)
    {
        if ( wxMessageBox(_T("Vuoi davvero Uscire?"), _T(""),
                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
        {
            event.Veto();
        }
    }


    void OnWizardPageChanging(wxWizardEvent& event)
    {
        wxConfigBase *pConfig = wxConfigBase::Get();
        pConfig->SetPath(_T("/Controls"));
        pConfig->Write(_T("/Controls/Text3")     , m_ctrl->GetValue().c_str());
    }

private:
    wxTextCtrl   * m_ctrl;
    DECLARE_EVENT_TABLE()
};



class PaginaWizard4 : public wxWizardPageSimple
{
public:

    PaginaWizard4(wxWizard *parent) : wxWizardPageSimple(parent)
    {

        (void)new wxStaticText(this, -1,
           _T(" Inserite l'indirizzo completo preceduto da http://")
           _T("\n")
           _T(" del vostro server Intranet  (preferibilmente Apache > 1.3)")
           _T("\n\n")
           _T(" Nella casella proponiamo il valore di default 127.0.0.1 per")
           _T("\n")
           _T(" un server installato su questo stesso computer")
           _T("\n\n")
           _T(" In una installazione classica il server dovrebbe avere")
           _T("\n")
           _T(" un indirizzo verosimilmente del tipo 192.168.0.x"));
        m_ctrl = new wxTextCtrl( this, -1, _T("http://127.0.0.1"), wxPoint(5, 120), wxSize(256,-1) );


    }

    void OnWizardCancel(wxWizardEvent& event)
    {
        if ( wxMessageBox(_T("Vuoi davvero Uscire?"), _T(""),
                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
        {
            event.Veto();
        }
    }

    void OnWizardPageChanging(wxWizardEvent& event)
    {
        wxConfigBase *pConfig = wxConfigBase::Get();
        pConfig->SetPath(_T("/Controls"));
        pConfig->Write(_T("/Controls/Text4")     , m_ctrl->GetValue().c_str());
    }

private:
    wxTextCtrl   * m_ctrl;
    DECLARE_EVENT_TABLE()
};




class PaginaWizard5 : public wxWizardPageSimple
{
public:

    PaginaWizard5(wxWizard *parent) : wxWizardPageSimple(parent)
    {

        m_bitmap = wxBITMAP(wiztest2);

        (void)new wxStaticText(this, -1,
           _T(" Definite l'intervallo tra due singoli downloads")
           _T("\n\n")
           _T(" Usate il cursore per definire il ritardo in secondi.\n"));

        m_slider = new wxSlider(this, 181, 0, 0, 100, wxPoint(18,90), wxSize(155,-1), wxSL_AUTOTICKS | wxSL_LABELS );

        m_slider->SetValue(4);
        m_slider->SetTickFreq(40, 0);


    }

    void OnWizardCancel(wxWizardEvent& event)
    {
        if ( wxMessageBox(_T("Vuoi davvero Uscire?"), _T(""),
                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
        {
            event.Veto();
        }
    }

    void OnWizardPageChanging(wxWizardEvent& event)
    {
        wxConfigBase *pConfig = wxConfigBase::Get();
        pConfig->Write(_T("/Controls/Slider1"), (long) m_slider->GetValue() );
    }

private:
    wxSlider   * m_slider;
    DECLARE_EVENT_TABLE()
};




class wxCheckboxPage : public wxWizardPage
{
public:
    wxCheckboxPage(wxWizard *parent,
                   wxWizardPage *prev,
                   wxWizardPage *next)
        : wxWizardPage(parent)
    {
        m_prev = prev;
        m_next = next;

        (void)new wxStaticText(this, -1,
           _T(" Se vuoi utilizzare Connection Alive per la tua Intranet devi")
           _T("\n")
           _T(" inserire nella prossima pagina l'indirizzo del Server Intranet.")
           _T("\n\n")
           _T(""));

        m_checkbox = new wxCheckBox(this, -1, _T(" Non ho alcuna Intranet e voglio saltare la prossima fase"),  wxPoint(5, 60));
    }

    virtual wxWizardPage *GetPrev() const { return m_prev; }
    virtual wxWizardPage *GetNext() const
    {
        wxConfigBase *pConfig = wxConfigBase::Get();
        if (m_checkbox->GetValue() != 1)
           pConfig->Write(_T("/Controls/ChkMaster3"), TRUE );
        else
           pConfig->Write(_T("/Controls/ChkMaster3"), FALSE);
        return m_checkbox->GetValue() ? m_next->GetNext() : m_next;
    }

private:
    wxWizardPage *m_prev,
                 *m_next;

    wxCheckBox *m_checkbox;
};



class Telecomando : public wxMiniFrame
{
public:
    Telecomando(wxWindow *parent);

private:
    DECLARE_EVENT_TABLE()
    void OnClose(wxCloseEvent& event);
};               

Telecomando    * m_telecomando;




class CanvasParent : public wxMiniFrame
{
public:
    CanvasParent(wxWindow *parent, wxWindowID id = -1, const wxString& title = _T(""),
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );
private:
    DECLARE_EVENT_TABLE()
    void OnClose(wxCloseEvent& event);
};

CanvasParent    *mini_frame;




class Istogramma: public wxScrolledWindow
{
public:
    Istogramma(CanvasParent *parent);
    void DisegnaIstogramma();
    void OnPaint();
private:
    DECLARE_EVENT_TABLE()
    wxIcon       m_std_icon;
    bool         m_clip;
};

Istogramma      *m_Istogramma;



