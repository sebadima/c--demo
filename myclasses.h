unit GGASSSAL;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, GGFORMBASE, Grids, DBGrids, RXDBCtrl, adstable, DB, adsdata,
  adsfunc, RxGrdCpt, Menus, ComCtrls, ToolWin, StdCtrls,
  Buttons, ToolEdit, Mask, ExtCtrls, Zdataset, ZQuery_go, ZAbstractRODataset,
  ZAbstractDataset, ZAbstractTable;

type
  TASSSAL = class(TFORMBASE)
    v_griglia: TRxDBGrid;
    ToolButton4: TToolButton;
    SpeedButton1: TSpeedButton;
    cmm: tzquery_go;
    cmm_assegna: tzquery_go;
    cmm_azzera: tzquery_go;
    SpeedButton2: TSpeedButton;
    cmm_assegna_tutto: tzquery_go;
    procedure FormShow(Sender: TObject);
    procedure v_grigliaKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure v_grigliaDblClick(Sender: TObject);
    procedure v_grigliaDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure SpeedButton1Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure SpeedButton2Click(Sender: TObject);
  protected
    procedure esegui_query;
    procedure selezione_dati;
  public
    cms_codice, cmt_codice: string;
    progressivo: integer;
    alla_data: tdate;

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

