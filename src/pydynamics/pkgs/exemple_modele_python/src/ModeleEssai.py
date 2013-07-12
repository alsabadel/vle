#-*- coding:utf-8 -*-

#******************************************************************************
#
# File ModeleEssai.py
#
#------------------------------------------------------------------------------
#
# Un modele Dynamics partiel
#
#------------------------------------------------------------------------------
#
#******************************************************************************

# !!! ModeleEssai installe sous pkgs-1.1/exemple_modele_python/pythonsrc

import PyDynamics
import convert

###############################################################################

class ModeleEssai(PyDynamics.Dynamics):
    
    def init(self, time): 
        print "********************************************"
        if time == 0.0:
            print "ModeleEssai.init retourne 1.0"
            return 1.0
        else :
            print "ModeleEssai.init retourne infinity"
            return PyDynamics.infinity

###############################################################################

def model_is_it_ok():

        print ""
        mon_dict = dict()
        mon_dict["cleA"] = "valeur_de_cleA"
        mon_dict["cleB"] = 999
        mon_dict["cleC"] = 88.8
        mon_dict["cleD"] = True
        print "type(mon_dict) : ", type(mon_dict), " , valeur de mon_dict : ", mon_dict
        mon_dict_value = convert.to_vlevalue(mon_dict)
        print "type(mon_dict_value) : ", type(mon_dict_value)

        print ""
        mon_list = list()
        mon_list.append( 678 )
        mon_list.append( "ffff" )
        mon_list.append( 7.4 )
        mon_list.append( False )
        print "type(mon_list) : ", type(mon_list), " , valeur de mon_list : ", mon_list
        mon_list_value = convert.to_vlevalue(mon_list)
        print "type(mon_list_value) : ", type(mon_list_value)

        #Ajout de mon_list dans le mon_dict (Un map et un set dans un map)
        mon_dict["cleZ"] = mon_list
        print "type(mon_dict) : ", type(mon_dict), " , valeur de mon_dict : ", mon_dict
        mon_dict_value = convert.to_vlevalue(mon_dict)
        print "type(mon_dict_value) : ", type(mon_dict_value)

        print "********************************************"
        print "Lecture des 'Values' produites"

        print ""
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
        print "=== CODE ModeleEssai.py du paquet exemple_modele_python"
        print "********************************************"

###############################################################################

