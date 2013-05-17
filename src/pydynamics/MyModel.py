#-*- coding:utf-8 -*-

#******************************************************************************
#
# File MyModel.py
#
#------------------------------------------------------------------------------
#
# Un modele Dynamics partiel
#
#------------------------------------------------------------------------------
#
#******************************************************************************

import testDynamics
import convert

###############################################################################

class MyModel(testDynamics.Dynamics):
    
    def output(self,time,events):

        # ecriture d'evenements dans events (external events)

        print "---------------------------------------------------------------"
        print "MyModel.output : "
        print ""

        print "********************************************"
        print "Construction de 'Values'"

        #
        # !!! Value : imbriquer dans une Value map et list...
        #

        print ""
        mon_bool = False
        print "type(mon_bool) : ", type(mon_bool), " , valeur de mon_bool : ", mon_bool
        mon_bool_value = convert.to_vlevalue(mon_bool)
        print "type(mon_bool_value) : ", type(mon_bool_value)

        print ""
        mon_int = 77
        print "type(mon_int) : ", type(mon_int), " , valeur de mon_int : ", mon_int
        mon_int_value = convert.to_vlevalue(mon_int)
        print "type(mon_int_value) : ", type(mon_int_value)

        print ""
        mon_float = float(77)
        print "type(mon_float) : ", type(mon_float), " , valeur de mon_float : ", mon_float
        mon_float_value = convert.to_vlevalue(mon_float)
        print "type(mon_float_value) : ", type(mon_float_value)

        print ""
        mon_str = "mon_texte"
        print "type(mon_str) : ", type(mon_str), " , valeur de mon_str : ", mon_str
        mon_str_value = convert.to_vlevalue(mon_str)
        print "type(mon_str_value) : ", type(mon_str_value)

        print ""
        mon_dict = dict()
        mon_dict["cleA"] = "valeur_de_cleA"
        mon_dict["cleB"] = 999
        mon_dict["cleC"] = 88.8
        mon_dict["cleD"] = True
        print "type(mon_dict) : ", type(mon_dict), " , valeur de mon_dict : ", mon_dict
        mon_dict_value = convert.to_vlevalue(mon_dict)
        print "type(mon_dict_value) : ", type(mon_dict_value)
        #Second Dict pour imbriquer un Dict dans un Dict
        print ""
        mon_dict2 = dict()
        mon_dict2["cleE"] = "valeur_de_cleE"
        mon_dict2["cleF"] = 111
        mon_dict2["cleG"] = 22.2
        mon_dict2["cleH"] = False
        print "type(mon_dict2) : ", type(mon_dict2), " , valeur de mon_dict2 : ", mon_dict2
        mon_dict2_value = convert.to_vlevalue(mon_dict2)
        print "type(mon_dict2_value) : ", type(mon_dict2_value)

        print ""
        mon_list = list()
        mon_list.append( 678 )
        mon_list.append( "ffff" )
        mon_list.append( 7.4 )
        mon_list.append( False )
        print "type(mon_list) : ", type(mon_list), " , valeur de mon_list : ", mon_list
        mon_list_value = convert.to_vlevalue(mon_list)
        print "type(mon_list_value) : ", type(mon_list_value)
        #Seconde List pour imbriquer une List dans une List
        print ""
        mon_list2 = list()
        mon_list2.append( 123 )
        mon_list2.append( "aaaa" )
        mon_list2.append( 2.5 )
        mon_list2.append( True )
        print "type(mon_list2) : ", type(mon_list2), " , valeur de mon_list2 : ", mon_list2
        mon_list2_value = convert.to_vlevalue(mon_list2)
        print "type(mon_list2_value) : ", type(mon_list2_value)

        #Ajout de mon_dict2 et mon_list dans le mon_dict (Un map et un set dans un map)
        mon_dict["cleY"] = mon_dict2
        mon_dict["cleZ"] = mon_list
        print "type(mon_dict) : ", type(mon_dict), " , valeur de mon_dict : ", mon_dict
        mon_dict_value = convert.to_vlevalue(mon_dict)
        print "type(mon_dict_value) : ", type(mon_dict_value)

        #Ajout de mon_dict2 et mon_list2 dans le mon_list (Un map et un set dans un set)
        mon_list.append( mon_dict2 )
        mon_list.append( mon_list2 )
        print "type(mon_list) : ", type(mon_list), " , valeur de mon_list : ", mon_list
        mon_list_value = convert.to_vlevalue(mon_list)
        print "type(mon_list_value) : ", type(mon_list_value)

        print "********************************************"
        print "Lecture des 'Values' produites"

        print ""
        valeur_python = convert.to_pyvalue( mon_bool_value )
        print "valeur python de mon_bool_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( mon_int_value )
        print "valeur python de mon_int_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( mon_float_value )
        print "valeur python de mon_float_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( mon_str_value )
        print "valeur python de mon_str_value : ", valeur_python
        print "et son type : ", type(valeur_python)

        print ""
        #print "type(mon_dict_value.get('cleA')) : ", type( mon_dict_value.get("cleA") )
        #print "mon_dict_value.get('cleA').getType() : ", mon_dict_value.get("cleA").getType()
        #print "mon_dict_value de 'cleA' : ", testDynamics.toString(mon_dict_value.get("cleA"))
        valeur_python = convert.to_pyvalue( mon_dict_value )
        print "valeur python de mon_dict_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print "lecture des elements  1 a 1 : "
        for k,v in valeur_python.iteritems() :
            print "key : ", k, "value : ", v

        print ""
        valeur_python = convert.to_pyvalue( mon_list_value )
        print "valeur python de mon_list_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print "lecture des elements 1 a 1 : "
        for e in valeur_python :
            print e

        print ""
        print "********************************************"
        print "Creation des evenements"

        print "    - eventB : Boolean"
        print "    - eventC : Integering"
        print "    - eventD : Double"
        print "    - eventE : String"
        eventA= self.buildEvent("PortA")
        eventB= self.buildEventWithABoolean("PortB", "NomAttributB", mon_bool) 
        eventC= self.buildEventWithAInteger("PortC", "NomAttributC", mon_int)
        eventD= self.buildEventWithADouble("PortD", "NomAttributD", mon_float)  
        eventE= self.buildEventWithAString("PortE", "NomAttributE", mon_str) 
        print "    - eventF : Map, String, Boolean, Double"
        eventF= self.buildEvent("PortF")
        eventF.putAttribute("Ma_Map",mon_dict_value)
	eventF.putAttribute("Mon_String",mon_str_value)
	eventF.putAttribute("Mon_Boolean",mon_bool_value)
	eventF.putAttribute("Mon_Double",mon_float_value)

        print "    - eventG : Set"
        eventG= self.buildEvent("PortG")
        eventG.putAttribute("NomAttributG",mon_list_value)

        print ""
        print "********************************************"
        print "Ajout des evenements a la liste d'evenements"

        events.append(eventA);
        events.append(eventB);   
        events.append(eventC); 
        events.append(eventD); 
        events.append(eventE);   
        events.append(eventF); 
        events.append(eventG); 
	

    def init(self, time): 
        if time == 0.0:
            return 1.0
        else :
            return testDynamics.infinity

    def externalTransition(self, time, events):
        print ""
        print "********************************************"
        print "Lecture des evenements de la liste d'evenements"
        print ""
        for event in events : 
            convert.GetEventValue( event )
            print ""
        print ""
        print "********************************************"

###############################################################################
## sans init_events

print ""
print "Initialisation du Modele..."
modelinit = testDynamics.DynamicsInit()
my_model = MyModel( modelinit )

print "Creation de la liste d'evenements externes..."
external_events = testDynamics.ExternalEventList()

print "Appels de methodes du Modele :"
time = 0.0
my_model.init( time )
my_model.output(0.0, external_events)
my_model.externalTransition( time, external_events )

###############################################################################
## avec init_events
#   
#   modelinit = testDynamics.DynamicsInit()
#   
#   print "Creation de la liste d'evenements init..."
#   init_events = testDynamics.InitEventList.create()
#   
#   # !!! remplacer my_model = MyModel( modelinit ) par :
#   my_model = MyModel( modelinit, init_events )
#   # !!! et dans constructeur MyModel, lire parametre dans init_events
#   
#   external_events = testDynamics.ExternalEventList()
#   time = 0.0
#   my_model.init( time )
#   my_model.output(0.0, external_events)
#   my_model.externalTransition( time, external_events )
#   
###############################################################################

