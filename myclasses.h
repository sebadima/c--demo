

____________________________________________________________________________

****business_plan*** rev 05/02/2010
____________________________________________________________________________

pubbliche.relazioni devono sostituire il marketing basato sulla pubblicita'  
quindi wikipedia-giornali locali-nazionali-articoli-blog-forum tipo 
html.it
___________________________________________________________________________

***Executive summary

che tipo di azienda e'
  una compagnia di sviluppo e assistenza software

Quali prodotti servizi? 
  -1 sviluppo di software specifico su commissione
  -2 pacchetti standard modificati per automazione aziendale
  -3 sviluppo di software destinato alla distribuzione commerciale 
  -4 servizi di hosting e posta elettronica certificata
  -5 servizi SISTEMISTICI AVANZATI (da implementare in questo doc.)
Integra e' partita come ditta di sviluppo di software per automazione aziendale
e nel tempo ha incontrato difficolta' nel processo di commercializzazione
e di assistenza clienti.
I maggiori successi riguardano l'automazione della fatturazione e l'assistenza
on site che nel futuro potrebbero diventare una cash cow per generare reddito
____________________________________________________________________________





____________________________________________________________________________

***Definire meglio i prodotti e vantaggi competitivi
  
  assistenza sistemistica: 
    -favorire la comunicazione pacchettizzando la proposta
     (definire prodotti e loro comunicazione) 
    -unire assistenza pc all'assistenza legale (Pec/Privacy/Sicurezza)
    -aggiungere lo sviluppo di piccoli software (GO) personalizzati.
  
  sviluppo software (creazione di programmi su misura):
    -curare il rapporto col cliente con ampia capacita' personalizzazione
     (curare dunque lo sviluppo tecnico)
    -abbandonare gradualmente prodotti basso livello)
     (focalizzandoti sul business primario)
    -abbracciare nuove tecnologie 
  
  sviluppo software (creazione di programmi per marketing diffuso):
    -il prodotto sara' basato su esigenze reali e con possibilita'
     superiori ai concorrenti in settori di mercato ristretto
     attualmente sei in posizione debole !!
     La soluzione e' quella di concentrare gli sforzi su settori di nicchia
     a basso contenuto di marketing ed elevato contenuto tecnico
     (es. sistema di firewall o protezione aziendale facile da configurare)
     -- unione delle metafore di QuickBooks e hacker ventenni --

  integrazione dei sistemi:(?)
    -installazione/configurazione/assistenza   su googlecode.com 
     (il vantaggio e' costituito dalla capacita' di personalizzare
     profondamente googlecode)     
____________________________________________________________________________



____________________________________________________________________________

La qualita' (affidabilita'-opzioni-semplicita') sembrano davvero una mazza sul 
mercato..... me ne accorgo studiando i delphi tools (mmaker rbuilder): vince 
chi ha il prodotto migliore.

puoi realizzare il prodotto migliore lavorando su utility con mercato di 
nicchia (waler extradev ggscandoc gui sql) e forzando la qualita' alzandola 
gradualmente con progettazione "senza debiti". Non e' impossibile, te la puoi 
giocare lavorando SUI concorrenti e le categorie molto tecniche preesistenti.
Il marketing gioca un ruolo inferiore se operi in un mercato tecnico...

Puoi dunque lavorare su tool tecnici (utility e lib) per soft-house (ne 
esistono centinaia di migliaia), con marketing b2b. Alternativo all'approccio 
End User alla Viaweb...puoi anche guadagnare con libri e sito, ma dipende dalla 
qualita'!! B2B PER UTILITY EVOLUTE!!
____________________________________________________________________________


___________________________________________________________________________

***TENDENZE E STATO DELL'ARTE

la richiesta per la informatizzazione sembra stabile nel lungo periodo
perche' il mercato e' in gran parte saturo nel sud-italia
Esistono delle nicchie di sviluppo nell'out sourcing professionale nel
campo dei settori simil-SAP e assistenza collegata.
Questo riguarda le grandi aziende e quindi si deve valutare la capacita'
di dialogare con quest'ultime.
Esiste una crescita sensibile nel campo della automazione di basso livello
con richiesta per l'assistenza spicciola
I segnali non sono positivi per quanto riguarda le medie aziende,
alle prese con la crisi economica e le difficolta' subite.

Il settore piu' stimolante dovrebbe diventare in futuro il software
verticalizzato, con forti competenze specifiche, barriere all'entrata, uno
studio di marketing mirato e, si spera, con lo sfruttamento delle competenze 
matematiche acquisite. 

Un altro settore in massima crescita e' quello della sicurezza aziendale:
essendo un settore tecnico a basso tasso di marketing puoi pensare di
creare un pacchetto autoinstallante e autoaggiornante "FACILE da USARE"
da vendere a 70 euro circa

____________________________________________________________________________



____________________________________________________________________________
***FATTORI DI SUCCESSO

il fattore principale dovrebbe essere 
la definizione di un bisogno mirato (sicurezza, ad esempio)
con la condizione di avere un prodotto solido, facile da usare.
Cio' impone di acquisire protocolli, tools e know how capaci di imporre
un framework al lavoro di sviluppo.
tools:
  snv, delphi 7, delphi 2007, 
  visual 2008, virtual box

Devi ampliare il mercato al Web o pubblicizzarti sul Web con prodotti
finiti e testabili fuori dal sud italia.
tools:
  adwords, google trends, sito+blog updated


____________________________________________________________________________



____________________________________________________________________________
***ANALISI DEI CONCORRENTI

I competitori hanno dimensioni quasi industriali e competenze di medio livello.
Cio' impone di puntare sullo qualita' tecnica e l'aggiornamento dei tools.


____________________________________________________________________________
***OBIETTIVI:
migliorare fatturato del 20% nel 2010
sviluppare kernel y12: pacchetto sicurezza
ottenere 2 contratti fornitura assistenza spicciola
ottenere 2 contratti fornitura assistenza sofware avanzata (gestionale open)
ampliare i contatti professionali non legati alla vendita
ampliare i contatti comerciali usando Pec

Per ottenere questo punteremo sulla qualita' emergenti di programma
Gestionale Open Rivisitato + Semplicita' d'uso y12.

Sfrutteremo inoltre a livello locale le occasioni fornite dalle novita' 
legislative, sviluppando una buona conoscenza della tematica aziendale
legata a sicurezza, aggiornamento, qualita'.
Useremo dei gadget e modulistica laser per i contatti di basso livello
e come interfaccia aziende superiori.
____________________________________________________________________________


    procedure visualizza_stampa_elabora; override;
  end;

implementation

{$R *.dfm}
uses ZZVAREXT, DMARC;

procedure TASSSAL.FormShow(Sender: TObject);
begin
  inherited;

  esegui_query;
end;

procedure TASSSAL.esegui_query;
var
  bookmark: tbookmark;
begin
  bookmark := query.getbookmark;

  query.close;
  query.parambyname('cms_codice').asstring := cms_codice;
  query.parambyname('cmt_codice').asstring := cmt_codice;
  query.open;

  query.gotobookmark(bookmark);
  query.freebookmark(bookmark);

  (v_griglia.columns.items[4].field as tfloatfield).displayformat := formato_display_quantita_zero;
  (v_griglia.columns.items[5].field as tfloatfield).displayformat := formato_display_importo_zero;
end;

procedure TASSSAL.v_grigliaKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if ((key = vk_f2) and (shift = [])) then
  begin
    speedbutton1click(speedbutton1);
  end
  else
  begin
    inherited;
    if ((key = vk_return) and (shift = [])) then
    begin
      selezione_dati;
    end;
  end;
end;

procedure TASSSAL.selezione_dati;
var
  i: word;
  progressivo: integer;
begin
  cmm.close;
  cmm.parambyname('progressivo').asinteger := query.fieldbyname('progressivo').asinteger;
  if query.fieldbyname('selezionato_sal').asstring = 'no' then
  begin
    cmm.parambyname('selezionato_sal').asstring := 'si';
  end
  else
  begin
    cmm.parambyname('selezionato_sal').asstring := 'no';
  end;
  cmm.execsql;

  esegui_query;
end;

procedure TASSSAL.visualizza_stampa_elabora;
begin
end;

procedure TASSSAL.v_grigliaDblClick(Sender: TObject);
begin
  inherited;
  if query.fieldbyname('progressivo').asinteger <> 0 then
  begin
    esegui_programma('GESCMM', query.fieldbyname('progressivo').asinteger, true);
  end;
end;

procedure TASSSAL.v_grigliaDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  inherited;
  try
    if (lowercase(column.fieldname) = 'selezionato_sal') then
    begin
      if query.fieldbyname('selezionato_sal').asstring = 'si' then
      begin
        v_griglia.canvas.brush.color := cllime;
        v_griglia.canvas.font.color := clblack;
      end;
    end;
  except
  end;

  v_griglia.defaultdrawcolumncell(rect, datacol, column, state);
end;

procedure TASSSAL.SpeedButton1Click(Sender: TObject);
begin
  inherited;

  cmm_assegna.close;
  cmm_assegna.parambyname('sal_progressivo').asinteger := progressivo;
  cmm_assegna.parambyname('cms_codice').asstring := cms_codice;
  cmm_assegna.parambyname('cmt_codice').asstring := cmt_codice;
  cmm_assegna.execsql;

  close;
end;

procedure TASSSAL.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  inherited;

  cmm_azzera.close;
  cmm_azzera.parambyname('cms_codice').asstring := cms_codice;
  cmm_azzera.parambyname('cmt_codice').asstring := cmt_codice;
  cmm_azzera.cmt_codice;
end;

procedure TASSSAL.SpeedButton2Click(Sender: TObject);
begin
  inherited;

  cmm_assegna_tutto.close;
  cmm_assegna_tutto.parambyname('sal_progressivo').asinteger := progressivo;
  cmm_assegna_tutto.parambyname('cms_codice').asstring := cms_codice;
  cmm_assegna_tutto.parambyname('cmt_codice').asstring := cmt_codice;
  cmm_assegna_tutto.execsql;

  close;
end;

initialization
  registerclass(tasssal);

end.

