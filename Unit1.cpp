//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
GasClass VozduhIncome;
GasClass VozduhToSmoke;
GasClass SmokeIncome;
SmokePlusVozduhGasClass SmokePlusVozduh;
ImpulseGasClass VozduhImpulse;
GasClass VozduhOutClean;

FilterClass Filter;
ContainerClass Container;
TLabel *LabelTrash;

float K=1.403;
int t=0;
void Work();
void UpdateUI();
void fixKey(TObject *Sender, System::WideChar &Key);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
DoubleBuffered=1;
randomize();
Form1->Chart1->Series[0]->Clear();
Form1->Chart1->Series[1]->Clear();

if(FileExists("filter.png")){
	Form1->Image1->Picture->LoadFromFile("filter.png");
}

Filter.Container=&Container;
TLabel *LabelTrash=new TLabel(Form1);
LabelTrash->Parent=Form1;
Container.LabelTrash=LabelTrash;
LabelTrash=NULL;

Container.LabelTrash->AutoSize=0;
Container.LabelTrash->Color=clBlack;
Container.LabelTrash->Transparent=0;
Container.LabelTrash->Caption="";
Container.LabelTrash->Height=129;
Container.LabelTrash->Width=169;
Container.LabelTrash->Left=16;
Container.LabelTrash->Top=236;

Form1->Image2->BringToFront();
Container.LabelTrash->BringToFront();
Form1->Image1->BringToFront();

VozduhIncome.SetTsim(20);
VozduhIncome.SetFPmax(500,0.6);
VozduhIncome.SetFzd(500);

SmokeIncome.SetTsim(250);
SmokeIncome.SetFPmax(120,0.1);
SmokeIncome.SetFzd(120);

VozduhToSmoke.SetTsim(VozduhIncome.GetT());
VozduhToSmoke.SetFPmax(VozduhIncome.GetF(),VozduhIncome.GetP());
VozduhToSmoke.SetFzd(VozduhIncome.GetF());

float zn=(K*SmokeIncome.GetF()+VozduhToSmoke.GetF());
float ch=(K*SmokeIncome.GetF()*SmokeIncome.GetT()+VozduhToSmoke.GetF()*VozduhToSmoke.GetT());
if(fabs(zn)>1e-8){
	SmokePlusVozduh.SetTsim(ch/zn);
}else{
	SmokePlusVozduh.SetTsim(50);
}

SmokePlusVozduh.SetFPmax(SmokeIncome.GetF()+VozduhToSmoke.GetF(),(SmokeIncome.GetP()+VozduhToSmoke.GetP())/2);
SmokePlusVozduh.SetFzd(360);

VozduhImpulse.SetTsim(20);
VozduhImpulse.SetFPmax(0.24,0.6);
VozduhImpulse.SetFzd(0);
VozduhImpulse.SetPzd(0.6);

VozduhOutClean.SetTsim(SmokePlusVozduh.GetT());
VozduhOutClean.SetFPmax(SmokePlusVozduh.GetF(),SmokePlusVozduh.GetP());
VozduhOutClean.SetFzd(SmokePlusVozduh.GetF());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
Work();
UpdateUI();
t++;
}
//---------------------------------------------------------------------------
void Work(){
VozduhIncome.OneMoreMoment();
SmokeIncome.OneMoreMoment();

float zn=(K*SmokeIncome.GetF()+VozduhToSmoke.GetF());
float ch=(K*SmokeIncome.GetF()*SmokeIncome.GetT()+VozduhToSmoke.GetF()*VozduhToSmoke.GetT());
float Tguess=0;
if(fabs(zn)>1e-8){
	Tguess=ch/zn;
}

VozduhToSmoke.SetTsim(VozduhIncome.GetT());
VozduhToSmoke.SetFPmax(VozduhIncome.GetF(),VozduhIncome.GetP());
if(Tguess>SmokePlusVozduh.GetTzd()+(1e-8)){
	VozduhToSmoke.SetFzd(VozduhToSmoke.GetF()+VozduhIncome.GetF()/100);
}else{
	VozduhToSmoke.SetFzd(VozduhToSmoke.GetF()-VozduhIncome.GetF()/100);
}
VozduhToSmoke.OneMoreMoment();

zn=(K*SmokeIncome.GetF()+VozduhToSmoke.GetF());
ch=(K*SmokeIncome.GetF()*SmokeIncome.GetT()+VozduhToSmoke.GetF()*VozduhToSmoke.GetT());
if(fabs(zn)>1e-8){
	Tguess=ch/zn;
}
SmokePlusVozduh.SetTsim(Tguess);
SmokePlusVozduh.SetFPmax(SmokeIncome.GetF()+VozduhToSmoke.GetF(),(SmokeIncome.GetP()+VozduhToSmoke.GetP())/2);
//SmokePlusVozduh.SetFzd(SmokeIncome.GetF()+VozduhToSmoke.GetF());
SmokePlusVozduh.OneMoreMoment();

int stopfly=Filter.OneMoreMoment((SmokePlusVozduh.GetKlapan()-(float)VozduhToSmoke.GetKlapan()/100*(0.75*SmokePlusVozduh.GetKlapan()))/10);//Максимально открытый воздух сделает 75% смеси чистой
Container.OneMoreMoment(stopfly);

VozduhImpulse.OneMoreMoment(Filter.GetPerepad());

if(VozduhImpulse.GetKlapan()>0){
	Filter.Impulse();
}

VozduhOutClean.SetTsim(SmokePlusVozduh.GetT());
VozduhOutClean.SetFPmax(SmokePlusVozduh.GetF(),SmokePlusVozduh.GetP());
VozduhOutClean.SetFzd(SmokePlusVozduh.GetF());
VozduhOutClean.OneMoreMoment();
}
//---------------------------------------------------------------------------
void UpdateUI(){
//Form1->Repaint();
Form1->Label1->Caption=Form1->Label1->Caption.sprintf(L"P (МПа) = %0.2f",VozduhImpulse.GetP());
Form1->Label9->Caption=Form1->Label9->Caption.sprintf(L"P перепад (МПа) = %0.2f",Filter.GetPerepad());
Form1->Label2->Caption=L"Клапан F (%) = "+IntToStr(VozduhImpulse.GetKlapan());

Form1->Label3->Caption=Form1->Label3->Caption.sprintf(L"Fдым (м3/ч) = %0.2f",SmokePlusVozduh.GetF());
Form1->Label7->Caption=Form1->Label7->Caption.sprintf(L"Fвозд (м3/ч) = %0.2f",VozduhToSmoke.GetF());
Form1->Label5->Caption=Form1->Label5->Caption.sprintf(L"Tдым (C) = %0.2f",SmokePlusVozduh.GetT());
Form1->Label4->Caption=L"Клапан Fдым (%) = "+IntToStr(SmokePlusVozduh.GetKlapan());
Form1->Label6->Caption=L"Клапан Fвозд (%) = "+IntToStr(VozduhToSmoke.GetKlapan());
Form1->TrackBar2->Position=SmokePlusVozduh.GetKlapan();
Form1->TrackBar3->Position=VozduhToSmoke.GetKlapan();

Form1->Label8->Caption=Form1->Label8->Caption.sprintf(L"Уровень (м) = %0.2f",Container.GetLevel());

Form1->Chart1->Series[0]->AddXY(t,SmokePlusVozduh.GetF());
Form1->Chart1->Series[1]->AddXY(t,VozduhToSmoke.GetF());

Form1->Image2->Canvas->FillRect(Rect(0,0,Form1->Image2->Width,Form1->Image2->Height));
for(int i=0;i<3;i++){
	for(int j=0;j<(160*2+23);j++){
		//Form1->Canvas->Pixels[Filter.PieceOfDirt[i][j]->Left][Filter.PieceOfDirt[i][j]->Top]=Filter.PieceOfDirt[i][j]->Color;
		Form1->Image2->Canvas->Pixels[Filter.PieceOfDirt[i][j]->Left][Filter.PieceOfDirt[i][j]->Top]=Filter.PieceOfDirt[i][j]->Color;
	}
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
Form1->TrackBar2->Enabled=!Form1->CheckBox2->Checked;
SmokePlusVozduh.SetAutoMode(Form1->CheckBox2->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
Form1->TrackBar3->Enabled=!Form1->CheckBox1->Checked;
VozduhToSmoke.SetAutoMode(Form1->CheckBox1->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
SmokePlusVozduh.SetKlapan(Form1->TrackBar2->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
VozduhToSmoke.SetKlapan(Form1->TrackBar3->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
VozduhImpulse.SetPzd(StrToFloat(Form1->LabeledEdit1->Text));
VozduhImpulse.SetTimeImpulseDuration(StrToFloat(Form1->LabeledEdit4->Text));
VozduhImpulse.SetTimeImpulsePeriodDuration(StrToFloat(Form1->LabeledEdit6->Text));
VozduhImpulse.SetPerepadzd(StrToFloat(Form1->LabeledEdit5->Text));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
VozduhImpulse.Impulse();
Filter.Impulse();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
VozduhImpulse.SetAutoMode(Form1->RadioGroup1->ItemIndex==1?true:false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
if(LabelTrash){
	delete LabelTrash;
	LabelTrash=NULL;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
Container.SetIsAuto(Form1->CheckBox3->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
Container.SetLevelzd(StrToFloat(Form1->LabeledEdit7->Text));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
Container.SetIsOn(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
SmokePlusVozduh.SetFzd(StrToFloat(Form1->LabeledEdit2->Text));
SmokePlusVozduh.SetTzd(StrToFloat(Form1->LabeledEdit3->Text));
}
//---------------------------------------------------------------------------
void fixKey(TObject *Sender, System::WideChar &Key){
if ((Key >= '0') && (Key <= '9')){  // цифры
}else if (Key == 8){  // <-
}else if ((Key == '.') || (Key == ',')){ // запятая
	if (((TLabeledEdit*)Sender)->Text.Pos(FormatSettings.DecimalSeparator)!=0){ // если запятая уже есть
		Key = 0;
	}else{ // если ещё нет
		if(((TLabeledEdit*)Sender)->GetTextLen()>0){
			Key = FormatSettings.DecimalSeparator;
		}else{
			Key = 0;
		}
	}
}else Key = 0; // не цифра
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit4KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit1KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit5KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit6KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit2KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit3KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabeledEdit7KeyPress(TObject *Sender, System::WideChar &Key)
{
fixKey(Sender,Key);
}
//---------------------------------------------------------------------------

