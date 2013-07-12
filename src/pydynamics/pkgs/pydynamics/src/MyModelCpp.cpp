/*
 * This file is part of VLE, a framework for multi-modeling, simulation
 * and analysis of complex dynamical systems.
 * http://www.vle-project.org
 *
 * Copyright (c) 2003-2013 Gauthier Quesnel <quesnel@users.sourceforge.net>
 * Copyright (c) 2003-2013 ULCO http://www.univ-littoral.fr
 * Copyright (c) 2007-2013 INRA http://www.inra.fr
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <iostream>
#include <string>

#include <vle/value/Value.hpp>
#include <vle/devs/Dynamics.hpp>

namespace vd = vle::devs;
namespace vv = vle::value;

namespace pydynamics {

class MyModelCpp : public vd::Dynamics
{
public:

    /*************************************************************************/
    /**
	 * Lit les parametres du modele
	 */
    MyModelCpp(const vd::DynamicsInit& init, const vd::InitEventList& events)
        : vd::Dynamics(init, events)
    {
        /* tous les parametres de events */
        std::cout << "------------------------------" << "\n";
        std::cout << "MyModelCpp constructeur, les parametres : " << "\n";

        for ( vv::Map::const_iterator it = events.begin();
              it != events.end(); ++it) {
            std::string key = it->first; //std::string value = it->second->writeToString();
            std::string value = it->second->writeToString();
            std::cout << "Le parametre de nom : " << key << "\n" << "   a pour valeur : " << value << "\n";

        }      
        std::cout << "\n";

        /* valeurs de parametres */

        if (events.exist("model_name")){
            p_model_name = vv::toString(events.get("model_name"));
            std::cout << "Le parametre 'model_name' a pour valeur : " << p_model_name << "\n";
        }

        if (events.exist("delay")){
            p_delay = vv::toDouble(events.get("delay"));
            std::cout << "Le parametre 'delay' a pour valeur : " << p_delay << "\n";
        }

        if (events.exist("param_map")){

            vv::Map param_map = events.getMap("param_map");
            std::string v = param_map.writeToString();
            std::cout << "Le parametre 'param_map' (un Map) contient : " << v << "\n";

            int un_integer = param_map.getInt("un_integer");
            std::cout << "... nom cle 'un_integer', valeur : " << un_integer << "\n";
            float un_double = param_map.getDouble("un_double");
            std::cout << "... nom cle 'un_double', valeur : " << un_double << "\n";

            vv::Set un_set = param_map.getSet("un_set");
            std::string value = un_set.writeToString();
            std::cout << "... nom cle 'un_set', valeur : " << value << "\n";
        }
    }

    /*************************************************************************/
    virtual ~MyModelCpp()
    {
    }

    /*************************************************************************/
    virtual vd::Time init(const vd::Time& /*time*/)
    {
        // std::cout << p_model_name << ".init \n";

        /* initialisation des donnees */

        m_choix = 0;

        mon_bool = false;

        mon_int = 77;

        mon_float = float(77);

        mon_str = "mon_texte";

        // mon_list 
        mon_list.addInt( 678 );
        mon_list.addString( "ffff" );
        mon_list.addDouble( 7.4 );
        mon_list.addBoolean( false );

        vv::Map& mon_dict2 = mon_list.addMap();
        mon_dict2.addString(  "cleE", "valeur_de_cleE" );
        mon_dict2.addInt(     "cleF", 111 );
        mon_dict2.addDouble(  "cleG", 22.2 );
        mon_dict2.addBoolean( "cleH", false );

        vv::Set& mon_list2 = mon_list.addSet();
        mon_list2.addInt(     123 );
        mon_list2.addString(  "aaaa" );
        mon_list2.addDouble(  2.5 );
        mon_list2.addBoolean( true );

        // mon_dict
        mon_dict.addString( "cleA", "valeur_de_cleA" );
        mon_dict.addInt( "cleB", 999 );
        mon_dict.addDouble( "cleC", 88.8 );
        mon_dict.addBoolean( "cleD", true );

        vv::Map& mon_dict2bis = mon_dict.addMap( "cleY" );
        mon_dict2bis.addString(  "cleE", "valeur_de_cleE" );
        mon_dict2bis.addInt(     "cleF", 111 );
        mon_dict2bis.addDouble(  "cleG", 22.2 );
        mon_dict2bis.addBoolean( "cleH", false );

        vv::Set& mon_list2bis = mon_dict.addSet( "cleZ" );
        mon_list2bis.addInt(     123 );
        mon_list2bis.addString(  "aaaa" );
        mon_list2bis.addDouble(  2.5 );
        mon_list2bis.addBoolean( true );

        return vd::Time(0); /* vd::infinity; */
    }

    /*************************************************************************/
    /**
	 * Construit et envoie evenement(s) en fonction de m_choix
	 */
    virtual void output(const vd::Time& time,
                        vd::ExternalEventList& outputs) const
    {
        // std::cout << p_model_name << ".output, time=" << time << ", " << "m_choix : " << m_choix << "\n";

        vd::ExternalEvent* evt;

        /* construit et envoie evenement(s) fonction de m_choix **************/
        std::ostringstream txtout;
        txtout << p_model_name << " envoie";
        switch ( m_choix ) {

        case 0 :
            // trace compte rendu
            txtout << " evt vide sur port out1";
            evt = buildEventWithAString( "out", "compte_rendu_envoi", txtout.str() );
            outputs.push_back( evt );

            // vide
            evt= buildEvent( "out1" );
            outputs.push_back( evt );

            break;

        case 1 :
            // trace compte rendu
            txtout << " bool sur port out2";
            evt = buildEventWithAString( "out", "compte_rendu_envoi", txtout.str() );
            outputs.push_back( evt );

            // bool
            evt = buildEventWithABoolean( "out2", "NomAttributB", mon_bool );
            outputs.push_back( evt );
            break;

        case 2 :

            // trace compte rendu
            txtout << " int sur port out1, float sur port out2, str sur port out3";
            evt = buildEventWithAString( "out", "compte_rendu_envoi", txtout.str() );
            outputs.push_back( evt );

            // int
            evt = buildEventWithAInteger( "out1", "NomAttributC", mon_int );
            outputs.push_back( evt );

            // float
            evt = buildEventWithADouble( "out2", "NomAttributD", mon_float );
            outputs.push_back( evt );

            // str
            evt = buildEventWithAString( "out3", "NomAttributE", mon_str );
            outputs.push_back( evt );
            break;

        case 3 :
            // trace compte rendu
            txtout << " dict sur port out1, list sur port out2, dict,str,bool,float sur port out3";
            evt = buildEventWithAString( "out", "compte_rendu_envoi", txtout.str() );
            outputs.push_back( evt );

            // dict
            evt = buildEvent( "out1" );
            evt->putAttribute( "Ma_Map", new vv::Map(mon_dict) );
            outputs.push_back( evt );

            // list
            evt = buildEvent( "out2" );
            evt->putAttribute( "NomAttributG", new vv::Set(mon_list) );
            outputs.push_back( evt );

            // dict,str,bool,float
            evt = buildEvent( "out3" );
            evt->putAttribute( "Ma_Map", new vv::Map(mon_dict) );
	        evt->putAttribute( "Mon_String", new vv::String(mon_str) );
	        evt->putAttribute( "Mon_Boolean", new vv::Boolean(mon_bool) );
	        evt->putAttribute( "Mon_Double", new vv::Double(mon_float) );
            outputs.push_back( evt );
            break;

        case 4 :
            // trace compte rendu
            txtout << " m_choix sur port out1";
            evt = buildEventWithAString( "out", "compte_rendu_envoi", txtout.str() );
            outputs.push_back( evt );

            // m_choix
            evt = new vd::ExternalEvent( "out1" );
            evt->putAttribute( "choix_message", new vv::Integer(m_choix) );
            outputs.push_back( evt );
            break;

        default :
            break;
        }
    }


    /*************************************************************************/
    virtual vd::Time timeAdvance() const
    {
        // std::cout << p_model_name << ".timeAdvance \n";

        return vd::Time(p_delay);
    }

    /*************************************************************************/
    virtual void internalTransition(const vd::Time& time)
    {

        /* determine (incremente) m_choix */
        m_choix++;

        /* traitement des donnees */

        mon_bool = false;

        mon_int = 77;

        mon_float = float(77);

        mon_str = "mon_texte";

        // ...
    }

    /*************************************************************************/
    /**
	 * Lit evenement(s) recus
	 */
    virtual void externalTransition(const vd::ExternalEventList& events,
                                    const vd::Time& time)
    {
        // std::cout << p_model_name << ".externalTransition \n";

        std::cout << "\n" << "------------------------------ " << p_model_name << ", time=" << time << "\n";

        vd::ExternalEventList::const_iterator it_event = events.begin();
        while (it_event != events.end()) {

            std::string port_name = (*it_event)->getPortName();

            std::cout << "\n";
            std::cout << "reception evenement sur port : " << port_name << "\n";

            if ( (*it_event)->haveAttributes() ){

                vv::Map map = (*it_event)->getAttributes();
                for ( vv::Map::const_iterator it_map = map.begin();
                      it_map != map.end(); ++it_map) {
                    std::string key = it_map->first;
                    std::string value = it_map->second->writeToString();

                    std::cout << "... nom attribut : " << key << "\n" << "    valeur attribut : " << value << "\n";
                }      

            } else {
                std::cout << "   ... sans attribut" << "\n";
            }

            ++it_event;
        }
    }

    /*************************************************************************/
    virtual void confluentTransitions(const vd::Time& time,
                                      const vd::ExternalEventList& events)
    {
        // std::cout << p_model_name << ".confluentTransitions \n";

        internalTransition(time);
        externalTransition(events, time);
    }

    /*************************************************************************/
    virtual vv::Value* observation(const vd::ObservationEvent& events ) const
    {
        // std::cout << p_model_name << ".observation \n";

        if ( events.onPort("m_choix") ){
            return buildInteger(m_choix);
        }
        return 0;
    }

    /*************************************************************************/
    virtual void finish()
    {
        // std::cout << p_model_name << ".finish \n";
    }

    /*************************************************************************/
    private:

        std::string p_model_name; /* nom du modele (indique dans les affichages ecran) */

        double p_delay; /* time advance */

        int m_choix; /* determine l'(les) evenement(s) construit/envoye(s) */

        /* les donnees du modele */

        bool mon_bool;
        int mon_int;
        float mon_float;
        std::string mon_str;
        vv::Set mon_list;
        vv::Map mon_dict;

};

} // namespace pydynamics

DECLARE_DYNAMICS(pydynamics::MyModelCpp)

