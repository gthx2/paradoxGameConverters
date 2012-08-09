#include "EU3History.h"
#include "..\CK2World\CK2Character.h"
#include "..\CK2World\CK2History.h"
#include "EU3Ruler.h"
#include "EU3Advisor.h"



EU3History::EU3History()
{
	when = date();
	monarch	= NULL;
	regent	= NULL;
	heir		= NULL;
	advisor	= NULL;
	capital	= "";
	owner		= "";
	culture	= "";
	discoverers.clear();
}


EU3History::EU3History(CK2History* src)
{
	when = src->getWhen();

	monarch	= NULL;
	regent	= NULL;
	heir		= NULL;
	advisor	= NULL;

	CK2Character* holder = src->getHolder();
	if (holder != NULL)
	{
		CK2Character* CK2Regent = holder->getRegent();
		if (CK2Regent != NULL)
		{
			regent	= new EU3Ruler(CK2Regent);
			heir		= new EU3Ruler(holder);
		}
		else
		{
			monarch = new EU3Ruler(holder);
		}
	}
	capital	= "";
	owner		= "";
	culture	= "";
	discoverers.clear();
}


EU3History::EU3History(date _when, EU3Ruler* _monarch, EU3Ruler* _regent, EU3Ruler* _heir, EU3Advisor* _advisor, string _capital, string _owner, string _culture, vector<string> _discoverers)
{
	when			= _when;
	monarch		= _monarch;
	regent		= _regent;
	heir			= _heir;
	advisor		= _advisor;
	capital		= _capital;
	owner			= _owner;
	culture		= _culture;
	discoverers	= _discoverers;
}


void EU3History::output(FILE* output)
{
	fprintf(output, "\t\t%d.%d.%d=\n", when.year, when.month, when.day);
	fprintf(output, "\t\t{\n");
	if (monarch != NULL)
	{
		monarch->outputAsMonarch(output);
	}
	if (regent != NULL)
	{
		regent->outputAsRegent(output);
		fprintf(output, "\t\t}\n");
		fprintf(output, "\t\t%d.%d.%d=\n", when.year, when.month, when.day);
		fprintf(output, "\t\t{\n");
	}
	if (heir != NULL)
	{
		heir->outputAsHeir(output);
	}
	if (advisor != NULL)
	{
		advisor->outputInProvince(output);
	}
	if (capital != "")
	{
		fprintf(output, "\t\t\tcapital=\"%s\"\n", capital.c_str());
	}
	if (owner != "")
	{
		fprintf(output, "\t\t\towner=\"%s\"\n", owner.c_str());
	}
	if (owner != "")
	{
		fprintf(output, "\t\t\tculture=%s\n", culture.c_str());
	}
	for (unsigned int i = 0; i < discoverers.size(); i++)
	{
		fprintf(output, "\t\t\tdiscovered_by=\"%s\"\n", discoverers[i].c_str());
	}
	fprintf(output, "\t\t}\n");
}