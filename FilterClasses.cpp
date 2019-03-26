//---------------------------------------------------------------------------
#pragma hdrstop
#include "FilterClasses.h"
#include <time.h>
#include <windows.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
GasClass::GasClass(){
this->IsAuto=1;
this->T=this->P=this->F=0;
this->Pmax=this->Fmax=100;
this->Tsim=20;
this->Fzd=100;
this->Klapan=0;
}
GasClass::~GasClass(){
}
//---------------------------------------------------------------------------
void GasClass::OneMoreMoment(){
if(this->IsAuto){
	float gisterezis=this->Fmax/100;
	if(this->Klapan<=0){
		//this->Klapan=this->F/this->Fmax*100;
		this->Klapan=1;
	}
	if(this->F>this->Fzd+gisterezis+(1e-8)){
		if(this->Klapan>1){
			this->Klapan--;
		}
	}else if(this->F<this->Fzd-gisterezis-(1e-8)){
		if(this->Klapan<100){
			this->Klapan++;
		}
	}
}
this->Simulation();
}
//---------------------------------------------------------------------------
void GasClass::Simulation(){
if(this->Klapan>0){
	this->F=((float)this->Klapan/100*this->Fmax)+(std::random(2)==1?1:-1)*((float)std::random(100)/10000);
	this->P=((float)this->Klapan/100*this->Pmax)+(std::random(2)==1?1:-1)*((float)std::random(100)/10000);
	this->T=this->Tsim+(std::random(2)==1?1:-1)*((float)std::random(100)/10000);
	if(this->F<0-(1e-8)){
		this->F=((float)std::random(100)/10000);
	}else if(this->F>this->Fmax+(1e-8)){
		this->F=this->Fmax-((float)std::random(100)/10000);
	}
	if(this->P<0-(1e-8)){
		this->P=((float)std::random(100)/10000);
	}else if(this->P>this->Pmax+(1e-8)){
		this->P=this->Pmax-((float)std::random(100)/10000);
	}
}else{
	this->T=this->F=this->P=0;
}
}
//---------------------------------------------------------------------------
float GasClass::GetT(){
return this->T;
}
//---------------------------------------------------------------------------
float GasClass::GetP(){
return this->P;
}
//---------------------------------------------------------------------------
float GasClass::GetF(){
return this->F;
}
//---------------------------------------------------------------------------
int GasClass::GetKlapan(){
return this->Klapan;
}
//---------------------------------------------------------------------------
void GasClass::SetFzd(float newFzd){
if((newFzd>0-(1e-8))&&(newFzd<this->Fmax+(1e-8))){
	this->Fzd=newFzd;
}
}
//---------------------------------------------------------------------------
void GasClass::SetKlapan(int newKlapan){
if((newKlapan>=0)&&(newKlapan<=100)){
	this->Klapan=newKlapan;
}
}
//---------------------------------------------------------------------------
void GasClass::SetAutoMode(bool newIsAuto){
this->IsAuto=newIsAuto;
}
//---------------------------------------------------------------------------
void GasClass::SetTsim(float newTsim){
this->Tsim=newTsim;
}
//---------------------------------------------------------------------------
void GasClass::SetFPmax(float newFmax,float newPmax){
if(newFmax>0+(1e-8)){
	this->Fmax=newFmax;
}
if(newPmax>0+(1e-8)){
	this->Pmax=newPmax;
}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
ImpulseGasClass::ImpulseGasClass(){
this->IsAuto=0;//ѕо перепаду
this->Pzd=0.6;
this->TimeImpulseDuration=1;
this->TimeImpulseStart=0;
this->TimeImpulsePeriodDuration=10;
this->TimeImpulsePeriodStart=0;
this->Perepadzd=0.2;
}
ImpulseGasClass::~ImpulseGasClass(){
}
//---------------------------------------------------------------------------
void ImpulseGasClass::OneMoreMoment(float PerepadNow){
if(this->Klapan>0){
	if((((double)clock()-this->TimeImpulseStart)/CLOCKS_PER_SEC)>this->TimeImpulseDuration+(1e-10)){
		this->Klapan=0;
		this->TimeImpulseStart=0;
		if(this->IsAuto){
			this->TimeImpulsePeriodStart=(double)clock();
		}
	}
}else{
	if(this->IsAuto){//ѕо периоду
		if((((double)clock()-this->TimeImpulsePeriodStart)/CLOCKS_PER_SEC)>this->TimeImpulsePeriodDuration+(1e-10)){
			this->Impulse();
		}
	}else{//ѕо перепаду
		if(PerepadNow>this->Perepadzd-(1e-8)){
			this->Impulse();
		}
	}
}
this->Simulation();
}
//---------------------------------------------------------------------------
void ImpulseGasClass::Impulse(){
	this->Klapan=this->Pzd/this->Pmax*100;
	this->TimeImpulseStart=(double)clock();
}
//---------------------------------------------------------------------------
void ImpulseGasClass::SetPzd(float newPzd){
if((newPzd>0-(1e-8))&&(newPzd<this->Pmax+(1e-8))){
	this->Pzd=newPzd;
}
}
//---------------------------------------------------------------------------
void ImpulseGasClass::SetPerepadzd(float newPerepadzd){
if(newPerepadzd>0-(1e-8)){
	this->Perepadzd=newPerepadzd;
}
}
//---------------------------------------------------------------------------
void ImpulseGasClass::SetTimeImpulseDuration(double newTimeImpulseDuration){
if(newTimeImpulseDuration>0+(1e-10)){
	this->TimeImpulseDuration=newTimeImpulseDuration;
}
}
//---------------------------------------------------------------------------
void ImpulseGasClass::SetTimeImpulsePeriodDuration(double newTimeImpulsePeriodDuration){
if(newTimeImpulsePeriodDuration>0+(1e-10)){
	this->TimeImpulsePeriodDuration=newTimeImpulsePeriodDuration;
}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
SmokePlusVozduhGasClass::SmokePlusVozduhGasClass(){
this->Tzd=100;
}
SmokePlusVozduhGasClass::~SmokePlusVozduhGasClass(){
}
//---------------------------------------------------------------------------
void SmokePlusVozduhGasClass::SetTzd(float newTzd){
if(newTzd>0-(1e-8)){
	this->Tzd=newTzd;
}
}
//---------------------------------------------------------------------------
float SmokePlusVozduhGasClass::GetTzd(){
return this->Tzd;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
FilterClass::FilterClass(){
this->Pin=0.1;
this->Pout=0.1;
this->Dirty=0;//max 255
for(int i=0;i<3;i++){
	for(int j=0;j<(160*2+23);j++){
		if(!PieceOfDirt[i][j]){
			if(j<160){
				PieceOfDirt[i][j]=new PieceOfDirtClass(37+i*51,67+j,-1,random(3)+5);
			}else if((j>=160)&&(j<320)){
				PieceOfDirt[i][j]=new PieceOfDirtClass(37+i*51+24,67+j-160,1,random(3)+5);
			}else if(j>=320){
				PieceOfDirt[i][j]=new PieceOfDirtClass(37+i*51+j-320,226,random(3)-1,random(3)+5);
			}
		}
	}
}
}
//-----------------------------------
FilterClass::~FilterClass(){
if(this->PieceOfDirt){
	for(int i=0;i<3;i++){
		for(int j=0;j<(160*2+23);j++){
			if(this->PieceOfDirt[i][j]){
				delete this->PieceOfDirt[i][j];
				this->PieceOfDirt[i][j]=NULL;
			}
		}
	}
}
}
//---------------------------------------------------------------------------
int FilterClass::OneMoreMoment(int intensity){
if(intensity<0){
	intensity=0;
}
if(intensity>10){
	intensity=10;
}
if(!this->IsFly){
	if(this->Dirty+intensity<255){
		this->Dirty+=intensity;
	}else if((this->Dirty<255)&&(intensity>0)){
		this->Dirty++;
	}
}
this->Pin=0.1+((float)this->Dirty/255*0.3);
this->Pout=(0.2+(this->Pin-(float)this->Dirty/255*(this->Pin-0.1)))/2;//Ёто все равно что (0.2+(х-х))/2, что математически безсмысленно, но зато логично. „ем выше загр€знение, тем слабее вли€ние, но чем ниже загр€знение, тем меньше разница в давлении.

int countfly=0,countstopflypower=0,ans=0;

if(this->Container){
	for(int i=0;i<3;i++){
		for(int j=0;j<(160*2+23);j++){
			ans=this->PieceOfDirt[i][j]->OneMoreMoment(this->IsFly?0:this->Dirty,this->Container->LabelTrash->Top);
			countfly+=ans==-2?1:0;
			countstopflypower+=ans>=0?ans:0;
		}
	}
	this->IsFly=countfly>0?1:0;
}
return countstopflypower;
}
//---------------------------------------------------------------------------
void FilterClass::Impulse(){
this->Dirty=0;
if(!this->IsFly){
	for(int i=0;i<3;i++){
		for(int j=0;j<(160*2+23);j++){
			this->PieceOfDirt[i][j]->StartToFly();
		}
	}
	this->IsFly=1;
}
}
//---------------------------------------------------------------------------
float FilterClass::GetPerepad(){
return fabs(this->Pin-this->Pout);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
ContainerClass::ContainerClass(){
this->IsAuto=1;
this->IsOn=0;
this->Level=0;
this->Levelzd=2;
}
ContainerClass::~ContainerClass(){
}
//---------------------------------------------------------------------------
void ContainerClass::OneMoreMoment(int addToLevel){
this->Level+=(float)addToLevel/255000;
if(this->Level>3+(1e-8)){
	this->Level=3;
	this->IsOn=1;
}
if(this->IsAuto){
	if(Level>Levelzd-(1e-8)){
		this->IsOn=1;
	}
}
if(this->IsOn){
	if(this->Level>(1e-8)){
		this->Level-=0.015;
	}else{
		this->Level=0;//на вс€кий случай и вместо проверки
		this->IsOn=0;
	}
}
if(this->LabelTrash){
	this->LabelTrash->Top=366-43*this->Level;
	this->LabelTrash->Height=43*this->Level;
}
}
//---------------------------------------------------------------------------
void ContainerClass::SetIsOn(bool newIsOn){
if((newIsOn)&&(!this->IsOn)){
	if(this->Level>(1e-8)){//вкл только если не пуст
		this->IsOn=newIsOn;
	}
}else{
	this->IsOn=newIsOn;
}
}
//---------------------------------------------------------------------------
float ContainerClass::GetLevel(){
return this->Level;
}
//---------------------------------------------------------------------------
void ContainerClass::SetLevelzd(float newLevelzd){
if((newLevelzd>(1e-8))&&(newLevelzd<3+(1e-8))){
	this->Levelzd=newLevelzd;
}
}
//---------------------------------------------------------------------------
void ContainerClass::SetIsAuto(bool newIsAuto){
this->IsAuto=newIsAuto;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
PieceOfDirtClass::PieceOfDirtClass(int newStartLeft,int newStartTop,int newMoveAddLeft,int newMoveAddTop){
this->Top=this->StartTop=newStartTop;
this->Left=this->StartLeft=newStartLeft;
this->MoveAddLeft=newMoveAddLeft;
this->MoveAddTop=newMoveAddTop;
this->Fly=0;
this->MoveLeftLeft=this->MoveLeftTop=0;
this->Power=0;
}
PieceOfDirtClass::~PieceOfDirtClass(){
}
//---------------------------------------------------------------------------
int PieceOfDirtClass::OneMoreMoment(int Dirty, int ContainerTop){
int ret=0;
if(this->Fly){
ret=-2;
	if(this->Top<ContainerTop){
		if(this->MoveLeftTop>0){
			this->Top+=this->MoveAddTop;
			this->MoveLeftTop--;
			if(this->Top>=ContainerTop){
				this->Color=(TColor)RGB(255,255,255);
			}
		}
		if(this->MoveLeftLeft>0){
			this->Left+=this->MoveAddLeft;
			this->MoveLeftLeft--;
		}
	}else{
		ret=this->Power;
		this->Fly=0;
		this->Top=this->StartTop;
		this->Left=this->StartLeft;
		this->Color=(TColor)RGB(255,255,255);
	}
}else{
	ret=-1;
	int R,G,B;
	if(Dirty<0){
		Dirty=0;
	}
	if(Dirty>255){
		Dirty=255;
	}
	this->Power=Dirty;//¬о врем€ полета это значение сохранитс€
	R=G=B=255-Dirty;
	this->Color=(TColor)RGB(R,G,B);
}
return ret;
}
//---------------------------------------------------------------------------
void PieceOfDirtClass::StartToFly(){
this->Fly=1;
this->MoveLeftLeft=1+random(21);
this->MoveLeftTop=500;
}
//---------------------------------------------------------------------------
