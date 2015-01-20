#ifndef __STD_UTILS_H__
#define __STD_UTILS_H__

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cctype>

#define umap unordered_map;
#define uset unordered_set;

#define SYS_PAUSE() system("PAUSE");

#define CNT_LOOP(num,i) for(i=0;i<num;++i)
#define CNT_2D_LOOP(m,n,i,j) for(i=0;i<m;++i)for(j=0;j<n;++j)

#define ITER_LOOP(container, iter) for((iter)=(container).begin();(iter)!=(container).end();(iter)++)

#define iCNT_LOOP(num,i) for(int i=0;i<num;++i)
#define iCNT_2D_LOOP(m,n,i,j) for(int i=0;i<m;++i)for(int j=0;j<n;++j)
#define iITER_LOOP(container, iter) for(auto iter=(container).begin();iter!=(container).end();iter++)

#define DISP(statement) std::cout<<statement<<endl
#define TRACE(var) std::cout<<#var<<" = "<<var<<endl
#define TRACE2(var1, var2) std::cout<<#var1<<" = "<<var1<<" , "<<#var2<<" = "<<var2<<endl

#define CV_SWAP(a,b,t) ((t) = (a), (a) = (b), (b) = (t))

#ifndef MIN
#	define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#	define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

#ifndef TMIN
#	define TMIN(a,b)  a = ((a) > (b) ? (b) : (a))
#endif

#ifndef TMAX
#	define TMAX(a,b)  a = ((a) < (b) ? (b) : (a))
#endif

#define CONDITION_TMAX(max_v, v, condition) if(condition) TMAX(max_v, v)
#define CONDITION_TMIN(min_v, v, condition) if(condition) TMIN(min_v, v)

#define DO_ON_MAX(max_v, v, expression) if(v > max_v) { max_v = v; expression;}
#define DO_ON_MIN(min_v, v, expression) if(v > min_v) { min_v = v; expression;}

#ifndef ABS
#define ABS(a)  ((a) < 0 ? (a)*(-1) : (a))
#endif

#ifndef ABS_DIFF
#	define ABS_DIFF(a,b)	(MAX(a,b)-MIN(a,b))
#endif

inline std::unordered_map<std::string, std::string> utFileParts(const std::string& file_name)
{
    using namespace std;
    std::unordered_map<std::string, std::string> ret;
    std::string temp = file_name.substr(0, file_name.find_last_of("/\\")+1);
    ret["path"] = temp;
    temp = file_name.substr(file_name.find_last_of("/\\")+1, file_name.find_last_of(".") - file_name.find_last_of("/\\") - 1);
    ret["nake"] = temp;
    temp = file_name.substr(file_name.find_last_of("."));
    ret["ext"] = temp;
    ret["fullfile"] = ret["nake"] + ret["ext"];
    return ret;
}


inline bool utFileExist(const std::string& filename)
{
	 std::fstream file;
	 file.open(filename,std::ios::in);
	 if(!file)
	 {
		 return false;
	 }
	 else
	 {
		 file.close();
		 return true;
	 }
}

std::vector<std::string> utFile2Strings(std::string filename);
std::string utFile2String(std::string filename);

template<typename T>
inline T max_v() {
    return (std::numeric_limits<T>::max)();
}

template<typename T>
inline T min_v() {
    return (std::numeric_limits<T>::min)();
}

#define MIN_VALUE(type) min_v<type>()
#define MAX_VALUE(type) max_v<type>()

inline void utString2File(std::string filename, std::string content)
{
    FILE* fp = fopen(filename.c_str(), "wt");
    fprintf(fp, "%s", content.c_str());
    fclose(fp);
    
}

template<typename T>
inline T utRetainPrecision(T float_num, int precision = 6)
{
    if (typeid(T) != typeid(float) && typeid(T) != typeid(double)) return float_num;
    float tens = 1.0f; bool sig = precision >= 0;
    while(precision--) tens *= 10;
    if(!sig) tens = 1.0 / tens;
    return round(float_num * tens) / tens;
}

inline void toLower(std::string & str) {
    std::transform(str.begin(), str.end(), str.begin(), std::tolower);
}

inline void toUpper(std::string & str) {
    std::transform(str.begin(), str.end(), str.begin(), std::toupper);
}

#endif
