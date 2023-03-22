#include "TimeConverterSystem.h"
#include<math.h>
#include<iostream>

using namespace std;

//格里高利历到儒略日 
void CommonTimeTojulianDay(const PCOMMONTIME pct, const PJULIANDAY pjd)
{
    if (pct->month <= 2)
    {
        pct->year -= 1;
        pct->month += 12;
    }
    double ut = pct->hour + pct->minute / 60.0 + pct->second / 3600.0;
    pjd->day = (int)(365.25 * pct->year) + (int)(30.6001 * (pct->month + 1)) + pct->day + ut / 24 + 1720981.5;
    // pjd->day=int(365.25*pct->year)+int(30.6001*(pct->month+1))+pct->day+int(1720981.5+pct->hour/24.0+pct->minute/1440.0+pct->second/86400.0);
};
//儒略日到格里高利历 
void JulianDayToCommontime(const PCOMMONTIME pct, const PJULIANDAY pjd){
    int J=int(pjd->day+0.5);
    int N=int(4*(J+68569)/146097);
    double L1=J+68569-int((N*146097+3)/4);
    int Y1=int(4000*(L1+1)/1461001);
    double L2=L1-int(1461*Y1/4)+31;
    int M1=int(80*L2/2447);
    int L3=int(M1/11); 
    pct->day=L2-int(2447*M1/80);
    pct->month=M1+2-12*L3;
    pct->year=int(100*(N-49)+Y1+L3);
    double T=fmod((pjd->day+0.5-int(pjd->day))*24,24);
    pct->hour=int(T);
    double T1=(T-pct->hour)*60;
    pct->minute=int(T1);
    pct->second=(T1-pct->minute)*60;
    
};
//年+年积日+天内秒到儒略日
void DayOfYearTojulianDay(const PDayOfYear doy, const PJULIANDAY pjd){
    JULIANDAY JD_first,JD_second;
    Gregoriancalendar pct_first {};
    pct_first.year=doy->year;
    pct_first.month=1;
    pct_first.day=1;
    CommonTimeTojulianDay(&pct_first,&JD_first);
    JD_second.day=doy->day+JD_first.day-1;
    pjd->day=JD_second.day+doy->second/86400;
};
//儒略日到年+年积日+天内秒
    void JulianDayTotDayOfYear(const PDayOfYear doy, const PJULIANDAY pjd){
    Gregoriancalendar pct_first {0};
    Gregoriancalendar pct_now {0};//xianzai de geligaolori
    JulianDayToCommontime(&pct_now,pjd);
    pct_first.year=pct_now.year;
    pct_first.month=1;
    pct_first.day=1;
    JULIANDAY pjd_first;//dangnian 1yue1ri rulueri
    CommonTimeTojulianDay(&pct_first,&pjd_first);
    doy->year=pct_now.year;
    doy->day=int(pjd->day-pjd_first.day); 
    doy->second=pct_now.second+pct_now.hour*3600+pct_now.minute*60;
};
// GPS时到儒略日 
void GPStimeToJulianday(const PGPSTIME gps, const PJULIANDAY pjd){
    pjd->day=2444244.5+gps->week*7+gps->second/86400;
};
//儒略日到GPS时 
void JuliandayToGPStime(const PGPSTIME gps, const PJULIANDAY pjd){
    gps->week=int((pjd->day-2444244.5)/7);
    gps->second=((pjd->day-2444244.5)/7-gps->week)*604800;
};
//BDS时到儒略日 
void BDStimeTojulianday(const PBDSTIME bds, const PJULIANDAY pjd){
    pjd->day=2453736.5+bds->week*7+bds->second/86400;
};
//儒略日到BDS时 
void JuliandayToBDStime(const PBDSTIME bds, const PJULIANDAY pjd){
    bds->week=int((pjd->day-2453736.5)/7);
    bds->second=((pjd->day-2453736.5)/7-bds->week)*604800;   
};
//Galileo时到儒略日 
void GaliletimeTojulianday(const PGalileotime gll, const PJULIANDAY pjd){
    pjd->day=2451412.5+gll->week*7+gll->second/86400;
};
//儒略日到Galileo 
void JuliandayToGalileotime(const PGalileotime gll, const PJULIANDAY pjd){
    gll->week=int((pjd->day-2451412.5)/7);
    gll->second=((pjd->day-2451412.5)/7-gll->week)*604800;
};
//GLONASST计时到儒略日 
void GLONASSTTojulianday(const PGALONASSTTIME gls, const PJULIANDAY pjd){
    Gregoriancalendar pct_1996 {};//定义1996+4*（N4-1）年1月1日
    pct_1996.year=1996+4*(gls->gapnum-1);
    pct_1996.month=1;
    pct_1996.day = 1;
    JULIANDAY JDn;//定义JDN
    CommonTimeTojulianDay(&pct_1996,&JDn);
    pjd->day=gls->day-1+gls->hour/24+gls->minute/1440+gls->second/86400+JDn.day;
};
//儒略日到GLONASST计时
void JuliandayToGLONASST(const PGALONASSTTIME gls, const PJULIANDAY pjd){
    Gregoriancalendar pct_now {0};//计算格里高利历
    JulianDayToCommontime(&pct_now,pjd);
    gls->gapnum=int((pct_now.year-1996)/4)+1;
    JULIANDAY JDn {0};
    Gregoriancalendar pct_1996 {0}; //定义1996年+4*（N4-1）年1月1日
    pct_1996.year=1996+4*(gls->gapnum-1);
    pct_1996.month=1;
    pct_1996.day = 1;
    CommonTimeTojulianDay(&pct_1996,&JDn);
    gls->day=pjd->day-JDn.day+1;
    gls->hour=pct_now.hour;
    gls->minute=pct_now.minute;
    gls->second=pct_now.second;
};




int main(){
    PCOMMONTIME pct = new Gregoriancalendar;
    PJULIANDAY pjd = new JULIANDAY;
    PDayOfYear pdoy = new DayOfYear;
    PGPSTIME pgt = new GPSTIME;
    PGalileotime pgll = new Galileotime;
    PBDSTIME pbds = new BDSTIME;
    PGALONASSTTIME pgls = new GALONASSTTIME;
    pct->year = 2022;
    pct->month = 12;
    pct->day = 12;
    pct->hour = 17;
    pct->minute = 38;
    pct->second = 45;

    cout << "转换之前的通用时（当地时间）：";
    cout << pct->year << "-" << pct->month << "-" << pct->day << "-" << pct->hour << ":" << pct->minute << ":" << pct->second << endl;
    cout << endl;
    CommonTimeTojulianDay(pct,pjd);//通用时->儒略日的转换
    cout << "通用时->儒略日的转换:";
    cout << pjd->day<< endl;
    cout << endl;

    Gregoriancalendar pct_eg {0};
    JulianDayToCommontime(&pct_eg,pjd);
    cout << pct_eg.year << "-" << pct_eg.month << "-" << pct_eg.day << "-" << pct_eg.hour << ":" << pct_eg.minute << ":" << pct_eg.second << endl;

    GPSTIME gps_eg {0};
    JuliandayToGPStime(&gps_eg,pjd);
    cout<<gps_eg.week << "-" << gps_eg.second<<endl;

    DayOfYear doy3 {0};
    JulianDayTotDayOfYear(&doy3,pjd);
    cout<<"nian"<<doy3.year << "-" << doy3.day << "-" << doy3.second << endl;

    JULIANDAY pjd10 {0};
    DayOfYearTojulianDay(&doy3,&pjd10);
    cout<<"julian"<<pjd10.day <<endl;
    
    JULIANDAY pjd1;
    GPStimeToJulianday(&gps1,&pjd1);
    cout<<pjd1.day<<endl;

    GALONASSTTIME gls1;
    JuliandayToGLONASST(&gls1,pjd);
    cout<<gls1.gapnum<<"-"<<gls1.day<<"-"<<gls1.hour<<"-"<<gls1.minute<<"-"<<gls1.second<<endl;

    JULIANDAY pjd2;
    GLONASSTTojulianday(&gls1,&pjd2);
    cout<<pjd2.day<<endl;
}

