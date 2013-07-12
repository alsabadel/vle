#-*- coding:utf-8 -*-

#******************************************************************************
#
# File MyModelPy.py
#
#------------------------------------------------------------------------------
#
# Un modele Dynamics partiel
#
#------------------------------------------------------------------------------
#
#******************************************************************************

# !!! MyModelPy installe sous pkgs-1.1/pydynamics/pythonsrc
# PyDynamics et convert installes sous pkgs-1.1/pydynamics_wrapper/wrapping

import PyDynamics
import convert

###############################################################################

class MyModelPy(PyDynamics.Dynamics):

    def __init__(self, model, events): 
        PyDynamics.Dynamics.__init__(self, model, events)
	print "**************** __init__ ******************"            
        self.m_choix = 1

        valeur_python = convert.to_pyvalue( events )
        print "valeur python de events : ", valeur_python
        print "lecture des elements  1 a 1 : "
        for k,v in valeur_python.iteritems() :
            print "key : ", k, "value : ", v

        if "delay" in valeur_python.keys() :
            self.p_delay = valeur_python["delay"]
            print "Le 'delay' est de : ", self.p_delay 
        else : 
            self.p_delay = 1.0

    def init(self, time): 
	print "****************** init ********************"
        print "valeur python de time : ", time
        print ""
        print "Construction de 'Values'"

        print ""
        self.mon_bool = False
        print "type(mon_bool) : ", type(self.mon_bool), " , valeur de mon_bool : ", self.mon_bool
        self.mon_bool_value = convert.to_vlevalue(self.mon_bool)
        print "type(mon_bool_value) : ", type(self.mon_bool_value)

        print ""
        self.mon_int = 77
        print "type(mon_int) : ", type(self.mon_int), " , valeur de mon_int : ", self.mon_int
        self.mon_int_value = convert.to_vlevalue(self.mon_int)
        print "type(mon_int_value) : ", type(self.mon_int_value)

        print ""
        self.mon_float = float(77)
        print "type(mon_float) : ", type(self.mon_float), " , valeur de mon_float : ", self.mon_float
        self.mon_float_value = convert.to_vlevalue(self.mon_float)
        print "type(mon_float_value) : ", type(self.mon_float_value)

        print ""
        self.mon_str = "mon_texte"
        print "type(mon_str) : ", type(self.mon_str), " , valeur de mon_str : ", self.mon_str
        self.mon_str_value = convert.to_vlevalue(self.mon_str)
        print "type(mon_str_value) : ", type(self.mon_str_value)

        print ""
        self.mon_dict = dict()
        self.mon_dict["cleA"] = "valeur_de_cleA"
        self.mon_dict["cleB"] = 999
        self.mon_dict["cleC"] = 88.8
        self.mon_dict["cleD"] = True
        print "type(mon_dict) : ", type(self.mon_dict), " , valeur de mon_dict : ", self.mon_dict
        self.mon_dict_value = convert.to_vlevalue(self.mon_dict)
        print "type(mon_dict_value) : ", type(self.mon_dict_value)
        #Second Dict pour imbriquer un Dict dans un Dict
        print ""
        self.mon_dict2 = dict()
        self.mon_dict2["cleE"] = "valeur_de_cleE"
        self.mon_dict2["cleF"] = 111
        self.mon_dict2["cleG"] = 22.2
        self.mon_dict2["cleH"] = False
        print "type(mon_dict2) : ", type(self.mon_dict2), " , valeur de mon_dict2 : ", self.mon_dict2
        self.mon_dict2_value = convert.to_vlevalue(self.mon_dict2)
        print "type(mon_dict2_value) : ", type(self.mon_dict2_value)

        print ""
        self.mon_list = list()
        self.mon_list.append( 678 )
        self.mon_list.append( "ffff" )
        self.mon_list.append( 7.4 )
        self.mon_list.append( False )
        print "type(mon_list) : ", type(self.mon_list), " , valeur de mon_list : ", self.mon_list
        self.mon_list_value = convert.to_vlevalue(self.mon_list)
        print "type(mon_list_value) : ", type(self.mon_list_value)
        #Seconde List pour imbriquer une List dans une List
        print ""
        self.mon_list2 = list()
        self.mon_list2.append( 123 )
        self.mon_list2.append( "aaaa" )
        self.mon_list2.append( 2.5 )
        self.mon_list2.append( True )
        print "type(mon_list2) : ", type(self.mon_list2), " , valeur de mon_list2 : ", self.mon_list2
        self.mon_list2_value = convert.to_vlevalue(self.mon_list2)
        print "type(mon_list2_value) : ", type(self.mon_list2_value)

        #Ajout de mon_dict2 et mon_list dans le mon_dict (Un map et un set dans un map)
        self.mon_dict["cleY"] = self.mon_dict2
        self.mon_dict["cleZ"] = self.mon_list
        print "type(mon_dict) : ", type(self.mon_dict), " , valeur de mon_dict : ", self.mon_dict
        self.mon_dict_value = convert.to_vlevalue(self.mon_dict)
        print "type(mon_dict_value) : ", type(self.mon_dict_value)

        #Ajout de mon_dict2 et mon_list2 dans le mon_list (Un map et un set dans un set)
        self.mon_list.append( self.mon_dict2 )
        self.mon_list.append( self.mon_list2 )
        print "type(mon_list) : ", type(self.mon_list), " , valeur de mon_list : ", self.mon_list
        self.mon_list_value = convert.to_vlevalue(self.mon_list)
        print "type(mon_list_value) : ", type(self.mon_list_value)
       
        return 0.0 #PyDynamics.infinity

    def timeAdvance(self):
        print "************** Time Advance ****************"
        print "Delay : ", self.p_delay
        return self.p_delay

    def output(self,time,events):
        print "***************** Output *******************"
        print "valeur python de time : ", time

        print ""
        print "********************************************"
        print "Creation des evenements"

        print "    - eventB : Boolean"
        print "    - eventC : Integering"
        print "    - eventD : Double"
        print "    - eventE : String"
        eventA= self.buildEvent("PortA")
        eventB= self.buildEventWithABoolean("PortB", "NomAttributB", self.mon_bool) 
        eventC= self.buildEventWithAInteger("PortC", "NomAttributC", self.mon_int)
        eventD= self.buildEventWithADouble("PortD", "NomAttributD", self.mon_float)  
        eventE= self.buildEventWithAString("PortE", "NomAttributE", self.mon_str) 
        print "    - eventF : Map, String, Boolean, Double"
        eventF= self.buildEvent("PortF")
        #eventF.putAttribute("Ma_Map",self.mon_dict_value)
	#eventF.putAttribute("Mon_String",self.mon_str_value)
	#eventF.putAttribute("Mon_Boolean",self.mon_bool_value)
	#eventF.putAttribute("Mon_Double",self.mon_float_value)

        print "    - eventG : Set"
        eventG= self.buildEvent("PortG")
        #eventG.putAttribute("NomAttributG", self.mon_list_value)        

        print ""
        print "********************************************"
        print "Ajout des evenements a la liste d'evenements"
        
        if self.m_choix == 0 :
            print "instuctions du choix ", self.m_choix
            events.append(eventA)
            events.append(eventB)  
        elif self.m_choix == 1 :   
            print "instuctions du choix ", self.m_choix
            events.append(eventC) 
            events.append(eventD)
        elif self.m_choix == 2 : 
            print "instuctions du choix ", self.m_choix
            events.append(eventE)  
            events.append(eventF)
        elif self.m_choix == 3 : 
            print "instuctions du choix ", self.m_choix
            events.append(eventE)  
            events.append(eventF) 
        else :
            print "instuctions du choix ", self.m_choix
            events.append(eventG)


    def confluentTransitions(self, time, events):
        print "**********  confluentTransition ************"        
        internalTransition(time)
        externalTransition(events, time)
    
    def observation(self, events):
        print "**************  observation ****************"
        if events.onPort("m_choix") :
            return convert.to_vlevalue(self.m_choix)
        else :
            return convert.to_vlevalue(0)
  
    def internalTransition(self, time):

        self.m_choix = self.m_choix + 1
        print "*********** internalTransition *************"
        print "valeur python de time : ", time

        print "********************************************"
        print "Lecture des 'Values' produites"
        print ""
        valeur_python = convert.to_pyvalue( self.mon_bool_value )
        print "valeur python de mon_bool_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( self.mon_int_value )
        print "valeur python de mon_int_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( self.mon_float_value )
        print "valeur python de mon_float_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( self.mon_str_value )
        print "valeur python de mon_str_value : ", valeur_python
        print "et son type : ", type(valeur_python)

        print ""
        valeur_python = convert.to_pyvalue( self.mon_dict_value )
        print "valeur python de mon_dict_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print "lecture des elements  1 a 1 : "
        for k,v in valeur_python.iteritems() :
            print "key : ", k, "value : ", v

        print ""
        valeur_python = convert.to_pyvalue( self.mon_list_value )
        print "valeur python de mon_list_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print "lecture des elements 1 a 1 : "
        for e in valeur_python :
            print e

        
    def externalTransition(self, events, time):
        print "*********** externalTransition *************"
        print "valeur python de time : ", time
        for event in events : 
            GetEventValue( event )
            print ""

###############################################################################
##
## Get the values of events of an EventList
##
###############################################################################
def GetEventValue( x ) :

    Name = x.getPortName ()
    print "Evenement(s) du %s."%Name
    if x.haveAttributes () == True :
        map = convert.to_pyvalue(x.getAttributes())
        for k,v in map.iteritems() :
            print "L'evenement de %s est :"%k, v
    else:
	print "Pas d'attribut pour l'evenement du port", Name
    
##############################################################

