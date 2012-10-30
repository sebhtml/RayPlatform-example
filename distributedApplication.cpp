/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#include <core/RankProcess.h>
#include "Application.h"
using namespace std;

int main(int argc,char**argv){

	RankProcess<Application> application;
	application.constructor(&argc,&argv);
	application.run();

	return 0;
}
