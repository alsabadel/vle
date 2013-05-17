#-*- coding:utf-8 -*-

#******************************************************************************
#
# File convert.py
#
#------------------------------------------------------------------------------
#
# Methodes to_vlevalue et to_pyvalue de conversion entre des valeurs de
# types python et Value (vle::value::Value)
#
#------------------------------------------------------------------------------
#
#******************************************************************************

import testDynamics

###############################################################################
##
## pyvalue to vlevalue
##
## !!! prendre en compte : XMLTYPE TUPLE TABLE MATRIX
##
###############################################################################
def to_vlevalue( x ):

    if isinstance( x, bool ) :
        val = testDynamics.Boolean.create( x )
    elif isinstance( x, int ) :
        val = testDynamics.Integer.create( x )
    elif isinstance( x, float ) :
        val = testDynamics.Double.create( x )
    elif isinstance( x, str ) :
        val = testDynamics.String.create( x )

    elif isinstance( x, dict ) :
        map = testDynamics.Map.create()
        for k,v in x.iteritems() :
            val = to_vlevalue( v )
            #print "type de val.clone() : ", type( val.clone() )
            map.toMap().add( k, val.clone() )
        val = map

    elif isinstance( x, list ) :
        set = testDynamics.Set.create()
        for v in x :
            val = to_vlevalue( v )
            set.toSet().add(val.clone())
        val = set

    elif isinstance( x, testDynamics.Value ) :
        val = x
    else :
        raise ValueError(u'Can\'t convert type %s in vle::value::Value' % type(x))

    return val

###############################################################################
##
## vlevalue to pyvalue
##
## !!! prendre en compte : XMLTYPE TUPLE TABLE MATRIX
##
## !!! enum type { BOOLEAN, INTEGER, DOUBLE, STRING, SET, MAP, TUPLE, ... };
##
###############################################################################
def to_pyvalue( x ) :

    # !!! enum type { BOOLEAN, INTEGER, DOUBLE, STRING, SET, MAP,
    #                 TUPLE, TABLE, XMLTYPE, NIL, MATRIX };

    if x.isBoolean() == True : # BOOLEAN
        val = testDynamics.toBoolean( x )
    elif x.isInteger() == True : # INTEGER
        val = testDynamics.toInteger( x )
    elif x.isDouble() == True : # DOUBLE
        val = testDynamics.toDouble( x )
    elif x.isString() == True : # STRING
        val = testDynamics.toString( x )
    elif x.isSet() == True : # SET
        set = testDynamics.toSetValue( x ).value()
        val = list()
        for v in set:
            val.append( to_pyvalue(v) )
    elif x.isMap() == True : # MAP
        map = testDynamics.toMapValue( x ).value()
        val = dict()
        for k,v in map.iteritems() :
            val[k] = to_pyvalue(v) 

    else:
		raise ValueError(u'Can\'t convert type to pyvalue')

    #print "to_pyvalue, type(val) : ", type( val )
    return val


###############################################################################
##
## Get the values of events of an EventList
##
###############################################################################
def GetEventValue( x ) :

    Name = x.getPortName ()
    print "Evenement(s) du %s."%Name
    if x.haveAttributes () == True :
        map = to_pyvalue(x.getAttributes())
        for k,v in map.iteritems() :
            print "L'evenement de %s est :"%k, v
    else:
	print "Pas d'attribut pour l'evenement du port", Name
    
##############################################################

