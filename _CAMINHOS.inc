
SET ThousandSep=',';
SET DecimalSep='.';
SET MoneyThousandSep=',';
SET MoneyDecimalSep='.';
SET MoneyFormat='R$ #,##0.00;-R$ #,##0.00';
SET TimeFormat='hh:mm:ss';
SET DateFormat='DD/MM/YYYY';
SET TimestampFormat='DD/MM/YYYY hh:mm:ss[.fff]';
SET FirstWeekDay=6;
SET BrokenWeeks=1;
SET ReferenceDay=0;
SET FirstMonthOfYear=1;
SET CollationLocale='pt-BR';
SET MonthNames='jan;fev;mar;abr;mai;jun;jul;ago;set;out;nov;dez';
SET LongMonthNames='janeiro;fevereiro;março;abril;maio;junho;julho;agosto;setembro;outubro;novembro;dezembro';
SET DayNames='seg;ter;qua;qui;sex;sáb;dom';
SET LongDayNames='segunda-feira;terça-feira;quarta-feira;quinta-feira;sexta-feira;sábado;domingo';

LET vShowCS = 0; 

SET vCurrentSelections              = ='Seleções: ' & if(vShowCS = 1, '  Click aqui para esconder a caixa da seleção' , if(isnull(GetCurrentSelections()), '', GetCurrentSelections(' / ', ': ', ',')));

SET v.ODS                           = '\\storage\QlikView\BI\QVD_ODS';
SET v.TDS                           = '\\storage\QlikView\BI\QVD_TDS';
SET v.TDW                           = '\\storage\QlikView\BI\QVD_TDW';
SET v.DW                            = '\\storage\QlikView\BI\QVD_DW';
SET v.INCLUDE                       = '\\storage\QlikView\BI\INCLUDE';


SET v.Cor.Azul                      = RGB(120,177,241);
SET v.Cor.Azul.Padrao               = RGB(3, 77, 162);
SET v.Cor.Azul.Escuro               = RGB(68,119,170);
SET v.Cor.Verde                     = ARGB(100,80,240,120);
SET v.Cor.Verde.Escuro              = RGB(37,187,154);
SET v.Cor.Vermelho                  = RGB(255,183,183);
SET v.Cor.Vermelho.Padrao           = RGB(237,27,36);
SET v.Cor.Vermelho.Escuro           = RGB(255,80,80);
SET v.Cor.Cinza.Claro               = RGB(235,235,235);
SET v.Cor.Cinza                     = RGB(140,140,140);
SET v.Cor.Cinza.Escuro              = RGB(70,70,70);
SET v.Cor.Amarelo                   = RGB(255,255,193);
SET v.Cor.Negativo                  = RGB(255,80,80);
SET v.Cor.Laranja.Escuro            = RGB(255,161,67);

SET v.Cor.Tropical                  = RGB(244,176,132);
SET v.Cor.P.L.                      = LightCyan(80);
SET v.Cor.Permanente                = RGB(217,217,217);

SET v.Cor.FP.Inverno                = RGB(155,194,230);
SET v.Cor.FP.Primavera              = RGB(255,153,255);
SET v.Cor.FP.AltoVerao              = RGB(255,204,59);
SET v.Cor.FP.Tropical               = RGB(244,176,132);

SET v.Cor.FP.Inverno.Percentual     = RGB(221,235,247);
SET v.Cor.FP.Primavera.Percentual   = RGB(255,204,255);
SET v.Cor.FP.AltoVerao.Percentual   = RGB(255,242,204);
SET v.Cor.FP.Tropical.Percentual    = RGB(248,203,143);

SET v.Cor.Estoque                   = RGB(255,255,193);
SET v.Cor.Demanda                   = RGB(255,217,102);
SET v.Cor.Demanda.Verde             = RGB(198,224,180);
SET v.Cor.Total.Referencias         = White();
SET v.Cor.Pedido.Compra             = RGB(200,145,255);
SET v.Cor.Requisicao.Compra         = RGB(185,220,240);
SET v.Cor.Sugestao.Positiva         = RGB(250,146,131);
SET v.Cor.Sugestao.Negativa         = RGB(172,230,240);
SET v.Cor.Sugestao.Zerada           = RGB(210,255,210);

SET v.Cor.NDE                       = RGB(180,230,250);
SET v.Cor.SUL                       = RGB(189,215,238);

SET v.Cor.LezALez                   = RGB(255,153,255);
SET v.Cor.Lunender                  = RGB(120,177,241);
SET v.Cor.Hangar                    = RGB(255,161,67);
SET v.Cor.Fico                      = RGB(51,204,102);
SET v.Cor.Alakazoo                  = RGB(200,145,255);
SET v.Cor.Graphene                  = RGB(255,204,59);
SET v.Cor.Hits                      = RGB(110,110,110);
SET v.Cor.MaisMulher                = RGB(255,80,80);

LET V_USUARIO = UPPER(Trim(Right(OSuser(), (Len(OSuser())-5))));
LET V_DOC_NOME = DocumentName();
LET V_CAMINHO_DOC = DocumentPath(); 
LET V_DATA_DOC = Floor(NOW());
LET V_HORA_DOC = NOW();

IF '$(V_USUARIO)' <> 'QC' Then

     INF:
     LOAD * Inline [
     USUARIO, NOME_DOCUMENTO, CAMINHO_DOCUMENTO, DATA_ACESSO, HORA_ACESSO
     '$(V_USUARIO)', '$(V_DOC_NOME)', '$(V_CAMINHO_DOC)', '$(V_DATA_DOC)', '$(V_HORA_DOC)'
     ];

     if FileSize( '$(v.ODS)\LOG_ACESSO_$(V_USUARIO).qvd' ) >0 then

          Concatenate     
          LOAD USUARIO, 
               NOME_DOCUMENTO, 
               CAMINHO_DOCUMENTO, 
               DATA_ACESSO,
               HORA_ACESSO
          // FROM $(v.ODS)\LOG_ACESSO*.qvd (qvd)
          FROM $(v.ODS)\LOG_ACESSO_$(V_USUARIO).qvd (qvd)
          Where Match(USUARIO, UPPER('$(V_USUARIO)'));

     end if

     IF ScriptErrorCount = 0 then     

          STORE INF INTO $(v.ODS)\LOG_ACESSO_$(V_USUARIO).qvd (qvd);   

     ENDIF

     DROP TABLE INF;
     
ENDIF
    
