#-*- coding:utf-8 -*-

#******************************************************************************
#
# File AdelCaribu.py
#
#------------------------------------------------------------------------------
#
# Un modele Dynamics partiel
#
#------------------------------------------------------------------------------
#
#******************************************************************************

# !!! AdelCaribu installe sous pkgs-1.1/pydynamics/pythonsrc
# PyDynamics et convert installes sous pkgs-1.1/pydynamics_wrapper/wrapping

import PyDynamics
import convert
#import pylab

from openalea.core.alea import load_package_manager, function
import sys
print sys.path
###############################################################################

pm = load_package_manager()
node_factory = pm['vle']['composite2CV_stub']
model_python_eval = function(node_factory)
 

class AdelCaribu(PyDynamics.Dynamics):

    def __init__(self, model, events): 
        PyDynamics.Dynamics.__init__(self, model, events)
        valeur_python = convert.to_pyvalue( events )
        if "model_name" in valeur_python.keys() :
            self.m_name = valeur_python["model_name"]
        print ""
        print "-----------------------------------------------"
	print "-------- ", self.m_name, " : __init__ --------------"            
        self.m_choix = 1

        print "valeur python de events : ", valeur_python
        print "lecture des elements  1 a 1 : "
        for k,v in valeur_python.iteritems() :
            print "key : ", k, "value : ", v

        self.conditions = valeur_python

        if "delay" in valeur_python.keys() :
            self.p_delay = valeur_python["delay"]
            print "Le 'delay' est de : ", self.p_delay 
        else : 
            self.p_delay = 1.0

        print ""

    def init(self, time): 
        print ""
        print "-----------------------------------------------"
	print "---------- ", self.m_name, " : init ----------------"
        print "valeur python de time : ", time
        print ""
        print "Construction de 'Values'"
	self.ports={}
        # /!\ donc convert.py -> gérer le none
        self.ALAI = -1.0
        self.RadPlant = -1.0
        print " ALAI = ", self.ALAI
        print " RadPlant = ", self.RadPlant
        print ""
        return 0.0 

    def timeAdvance(self):
        print ""
        print "-----------------------------------------------"
	print "----- ", self.m_name, " : Time Advance -------------"
        print "Delay : ", self.p_delay
        print ""
        return self.p_delay


    def output(self,time,events):
        print ""
        print "-----------------------------------------------"
	print "--------- ", self.m_name, " : output ---------------" 
        print "valeur python de time : ", time

        eventALAI= self.buildEvent("ALAI")
        eventALAI.putAttribute("AttrALAI", convert.to_vlevalue(float(self.ALAI)))
        eventRadPlant = self.buildEvent("RadPlant")
        eventRadPlant.putAttribute("AttrRadPlant", convert.to_vlevalue(float(self.RadPlant)))       

        events.append(eventALAI)
        events.append(eventRadPlant) 
        
        print "Valeur de ALAI", convert.to_pyvalue(convert.to_vlevalue(self.ALAI)) , self.ALAI
        print "Valeur de RadPlant", convert.to_vlevalue(self.RadPlant), self.RadPlant
        for event in events :
            print "Envoie de l'évènement :", event.getPortName()
        print ""

    def confluentTransitions(self, time, events):
        print ""
        print "-----------------------------------------------"
	print "--- ", self.m_name, " : confluentTransition --------" 
        print "valeur python de time : ", time      
        internalTransition(time)
        externalTransition(events, time)
        print ""
    
    def observation(self, events):
        #print ""
        #print "-----------------------------------------------"
	#print "------- ", self.m_name, " : observation ------------" 
        #print ""
        if events.onPort("m_choix") :
            return convert.to_vlevalue(self.m_choix)
        elif events.onPort("RAD_recu") :
	    try:
                return convert.to_vlevalue(self.ports['MicroMeteo']['RAD'])      	    
	    except KeyError:
	        return convert.to_vlevalue(0)
        elif events.onPort("TT_recu") :
	    try:
                return convert.to_vlevalue(self.ports['MicroMeteo']['TT'])      	    
	    except KeyError:
	        return convert.to_vlevalue(0)
        elif events.onPort("ALAI") :
            return convert.to_vlevalue(self.ALAI)
        elif events.onPort("RadPlant") :
            return convert.to_vlevalue(self.RadPlant) 
        else :
            return convert.to_vlevalue(0)
 
  
    def internalTransition(self, time):
        self.m_choix = self.m_choix + 1
        self.density = 5.0
	#print "AttrRad:",self.ports['RAD']['AttrRAD']
        print "Ports :", self.ports
	try:
      	    self.ALAI, self.RadPlant = model_python_eval(self.ports['MicroMeteo']['RAD'],self.ports['MicroMeteo']['TT'],self.conditions['density'])
	except KeyError:
	    self.ALAI,self.RadPlant = -1,-1
        print ""
        print "-----------------------------------------------"
	print "--- ", self.m_name, " : internalTransition ---------" 
        print "valeur python de time : ", time
        #self.ALAI = self.ALAI+1;
        #self.RadPlant = self.RadPlant+2;
        print "valeur python de ALAI : ", self.ALAI
        print "valeur python de RadPlant : ", self.RadPlant
        print ""
        
    def externalTransition(self, events, time):
        print ""
        print "-----------------------------------------------"
	print "--- ", self.m_name, " : externalTransition ---------" 
        print "valeur python de time : ", time
        for event in events : 
            self.ports.update(GetEventValue( event ))
            print ""
        print ""

###############################################################################
##
## Get the values of events of an EventList
##
###############################################################################
def GetEventValue( x ) :

    Name = x.getPortName ()
    print "Evenement(s) du port %s."%Name
    if x.haveAttributes () == True :
        map = convert.to_pyvalue(x.getAttributes())
        for k,v in map.iteritems() :
            print "L'evenement recus du port %s est :"%k, v
    else:
	print "Pas d'attribut pour l'evenement du port", Name
    return {Name:map}
	
    
##############################################################

