#ifndef XML_H_INCLUDED
#define XML_H_INCLUDED

void ReadXmlFile(char *filename,char *attribut[]);
void getXml(xmlNode * node, int i,char *attribut[]);
int is_leaf(xmlNode * node);

void modifyXml(char * filename);

void readAlarmXmlFile(char *filename, struct alarm anAlarm);
void getAlarmXml(xmlNode * node,int i,  struct alarm anAlarm);

#endif // XML_H_INCLUDED
