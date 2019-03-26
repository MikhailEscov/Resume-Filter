//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "FilterClasses.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabeledEdit *LabeledEdit1;
	TButton *Button1;
	TGroupBox *GroupBox2;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *CheckBox2;
	TLabeledEdit *LabeledEdit2;
	TTrackBar *TrackBar2;
	TButton *Button2;
	TLabel *Label5;
	TLabeledEdit *LabeledEdit3;
	TLabel *Label6;
	TTrackBar *TrackBar3;
	TLabel *Label7;
	TLabeledEdit *LabeledEdit4;
	TRadioGroup *RadioGroup1;
	TLabeledEdit *LabeledEdit5;
	TLabeledEdit *LabeledEdit6;
	TButton *Button3;
	TCheckBox *CheckBox1;
	TGroupBox *GroupBox3;
	TButton *Button4;
	TLabeledEdit *LabeledEdit7;
	TLabel *Label8;
	TCheckBox *CheckBox3;
	TLabel *Label9;
	TImage *Image1;
	TChart *Chart1;
	TImage *Image2;
	TButton *Button5;
	TLineSeries *Series1;
	TLineSeries *Series2;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall TrackBar2Change(TObject *Sender);
	void __fastcall TrackBar3Change(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall LabeledEdit4KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LabeledEdit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LabeledEdit5KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LabeledEdit6KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LabeledEdit2KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LabeledEdit3KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LabeledEdit7KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
