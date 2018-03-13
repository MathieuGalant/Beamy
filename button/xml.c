#include <time.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include <fmod.h>
#include <dirent.h>
#include "definition.h"




void readXmlFile(char *filename,  char * attribut[])
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;


    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL)
    {
        printf("Could not parse the XML file");
    }

    root_element = xmlDocGetRootElement(doc);

    getXml(root_element,0,attribut);

    xmlFreeDoc(doc);

    xmlCleanupParser();
    xmlCleanupParser();

}


void getXml(xmlNode * node,int i,  char *attribut[])
{


    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
      //    printf("%c%s:%s\n", '-', node->name, is_leaf(node)?xmlNodeGetContent(node):xmlGetProp(node, "id"));
          if (is_leaf(node))
          {
            attribut[i]=xmlNodeGetContent(node);
            i++;

          }
        }
        getXml(node->children,i, attribut);
        node = node->next;


    }

}

int is_leaf(xmlNode * node)
{
  xmlNode * child = node->children;
  while(child)
  {
    if(child->type == XML_ELEMENT_NODE) return 0;

    child = child->next;
  }

  return 1;
}



void modifyXml(char * filename)
{
    xmlDoc *doc = xmlParseFile(filename);
    xmlNode *root_element = NULL;
    xmlNode * node=NULL;
    root_element = xmlDocGetRootElement(doc);
    node=root_element->children;
    node=node->next;
  //  printf("%s",xmlNodeGetContent(node));
    xmlNodeSetContent(node, (xmlChar*)"0");


    xmlSaveFileEnc(filename, doc, "UTF-8");
}




void readAlarmXmlFile(char *filename, struct alarm anAlarm)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;


    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL)
    {
        printf("Could not parse the XML file");
    }

    root_element = xmlDocGetRootElement(doc);

    getAlarmXml(root_element,0,anAlarm);

    xmlFreeDoc(doc);

    xmlCleanupParser();
    xmlCleanupParser();

}


void getAlarmXml(xmlNode * node,int i,  struct alarm anAlarm)
{


    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
      //    printf("%c%s:%s\n", '-', node->name, is_leaf(node)?xmlNodeGetContent(node):xmlGetProp(node, "id"));
          if (is_leaf(node))
          {
            switch(i)
            {
         //       case 0: anAlarm.day=xmlNodeGetContent(node);
                case 1: anAlarm.hour=xmlNodeGetContent(node);
                case 2: anAlarm.min=xmlNodeGetContent(node);
                case 3: strcpy(anAlarm.musicName,xmlNodeGetContent(node));
                case 4: anAlarm.state=xmlNodeGetContent(node);
                case 5: anAlarm.delay=xmlNodeGetContent(node);
                case 6: strcpy(anAlarm.path,xmlNodeGetContent(node));

            }

            i++;

          }
        }
        getAlarmXml(node->children,i, anAlarm);
        node = node->next;


    }

}
