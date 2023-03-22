#ifndef __GPS_TIME_H__
#define __GPS_TIME_H__

//定义格里高利历日期
typedef struct tagGregoriancalendar{
    double year;
    double month;
    double day;
    double hour;
    double minute;
    double second;
}Gregoriancalendar;
typedef Gregoriancalendar *PCOMMONTIME;
//定义儒略日
typedef struct{
    double day;
    double second;
}JULIANDAY;
typedef JULIANDAY *PJULIANDAY;
//定义年+年积日+天内秒
typedef struct{
    double year;
    double day;
    double second;
}DayOfYear;
typedef DayOfYear *PDayOfYear;
//定义GPS时周+周内秒
typedef struct tagGPSTIME{
    double week;
    double second;
}GPSTIME;
typedef GPSTIME *PGPSTIME;
//定义BDS时周+周内秒
typedef struct tagBDSTIME{
    double week;
    double second;
}BDSTIME;
typedef BDSTIME *PBDSTIME;
//定义Galileo周+周内秒
typedef struct tagGalileotime{
    double week;
    double second;
}Galileotime;
typedef Galileotime *PGalileotime;
//定义GLONASST时
typedef struct tagGALONASSTTIME{
    double gapnum;
    double day;
    double hour;
    double minute;
    double second;
}GALONASSTTIME;
typedef GALONASSTTIME *PGALONASSTTIME;


#ifdef __cplusplus
extern "C" {
#endif


//格里高利历到儒略日
void CommonTimeTojulianDay(const PCOMMONTIME pct, const PJULIANDAY pjd); 
//儒略日到格里高利历
void JulianDayToCommontime(const PCOMMONTIME pct, const PJULIANDAY pjd);
//年+年积日+天内秒到儒略日
void DayOfYearTojulianDay(const PDayOfYear doy, const PJULIANDAY pjd);
//儒略日到年+年积日+天内秒
void JulianDayToDayOfYear(const PDayOfYear doy, const PJULIANDAY pjd);
// GPS时到儒略日
void GPStimeToJulianday(const PGPSTIME gps, const PJULIANDAY pjd);
//儒略日到GPS时
void JuliandayToGPStime(const PGPSTIME gps, const PJULIANDAY pjd);
//BDS时到儒略日
void BDStimeTojulianday(const PBDSTIME bds, const PJULIANDAY pjd);
//儒略日到BDS时
void JuliandayToBDStime(const PBDSTIME bds, const PJULIANDAY pjd);
//Galileo时到儒略日
void GaliletimeTojulianday(const PGalileotime gll, const PJULIANDAY pjd);
//儒略日到Galileo
void JuliandayToGalileotime(const PGalileotime gll, const PJULIANDAY pjd);
//GLONASST计时到儒略日
void GLONASSTTojulianday(const PGALONASSTTIME gls, const PJULIANDAY pid);
//儒略日到GLONASST计时
void JuliandayToGLONASST(const PGALONASSTTIME gls, const PJULIANDAY pjd);




#ifdef __cplusplus
}
#endif

#endif /* __GPS_TIME_H__ */