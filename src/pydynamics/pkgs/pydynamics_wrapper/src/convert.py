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

import PyDynamics

###############################################################################
##
## pyvalue to vlevalue
##
## !!! prendre en compte : XMLTYPE TUPLE TABLE MATRIX
##
###############################################################################
def to_vlevalue( x ):

    if isinstance( x, bool ) :
        val = PyDynamics.Boolean.create( x )
    elif isinstance( x, int ) :
        val = PyDynamics.Integer.create( x )
    elif isinstance( x, float ) :
        val = PyDynamics.Double.create( x )
    elif isinstance( x, str ) :
        val = PyDynamics.String.create( x )

    elif isinstance( x, dict ) :
        map = PyDynamics.Map.create()
        for k,v in x.iteritems() :
            val = to_vlevalue( v )
            #print "type de val.clone() : ", type( val.clone() )
            map.toMap().add( k, val.clone() )
        val = map
    # /!\ faire le test pour savoir si c'est itérable 
    # import collections
    # if isinstance(e, collections.Iterable):
    elif isinstance( x, list ) :
        set = PyDynamics.Set.create()
        for v in x :
            val = to_vlevalue( v )
            set.toSet().add(val.clone())
        val = set

    elif isinstance( x, PyDynamics.Value ) :
        val = x
    # /!\ gérer si null
    #elif x is None :
    #    val = PyDynamics.Null.create().clone()!!!
    else :
        raise ValueError(u'Can\'t convert type %s in vle::value::Value' % type(x))

    return val

###############################################################################
##
## vlevalue to pyvalue
##
## !!! prendre en compte : XMLTYPE TUPLE TABLE MATRIX
## enum type { BOOLEAN, INTEGER, DOUBLE, STRING, SET, MAP, TUPLE, ... };
##
###############################################################################
def to_pyvalue( x ) :

    type_value = x.getType()

    if x.isBoolean() : # BOOLEAN
        val = PyDynamics.toBoolean( x )
    elif x.isInteger() : # INTEGER
        val = PyDynamics.toInteger( x )
    elif x.isDouble() : # DOUBLE
        val = PyDynamics.toDouble( x )
    elif x.isString() : # STRING
        val = PyDynamics.toString( x )
    elif x.isSet() : # SET
        set = PyDynamics.toSetValue( x ).value()
        val = list()
        for v in set:
            val.append( to_pyvalue(v) )
    elif x.isMap() : # MAP
        map = PyDynamics.toMapValue( x ).value()
        val = dict()
        for k,v in map.iteritems() :
            val[k] = to_pyvalue(v) 
    # /!\ gérer si null
    #elif x.IsNullValue() : # NULL
    #    val = None

    else:
		raise ValueError(u'Can\'t convert type %s to pyvalue' % type_value)

    #print "to_pyvalue, type(val) : ", type( val )
    return val

##############################################################

