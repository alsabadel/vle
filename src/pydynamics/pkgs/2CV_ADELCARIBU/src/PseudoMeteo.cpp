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

class PseudoMeteo : public vd::Dynamics
{
public:

    /*************************************************************************/
    /**
	 * Lit les parametres du modele
	 */
    PseudoMeteo(const vd::DynamicsInit& init, const vd::InitEventList& events)
        : vd::Dynamics(init, events)
    {
        /* tous les parametres de events */
        std::cout << "------------------------------" << "\n";
        std::cout << "PseudoMeteo constructeur, les parametres : " << "\n";

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
    virtual ~PseudoMeteo()
    {
    }

    /*************************************************************************/
    virtual vd::Time init(const vd::Time& /*time*/)
    {
        // std::cout << p_model_name << ".init \n";

        /* initialisation des donnees */

        m_choix = 0;
        RAD = 1;
        TT = 1;
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

        vd::ExternalEvent* MicroMeteo;

        /* construit et envoie evenement(s) fonction de m_choix **************/
        std::ostringstream txtout;
        std::cout << "-----------------------------------------------" << "\n";
        std::cout << "----- " << p_model_name << " output ----------------------\n";
 
        std::cout << "Envoie de l'évènement : RAD = " << RAD  << "\n";
        std::cout << "Envoie de l'évènement : TT = " << TT  << "\n";
        MicroMeteo = buildEvent("MicroMeteo");
        //RAD = buildEventWithADouble( "RAD", "AttrRAD", mon_double );
        MicroMeteo->putAttribute("RAD",new vle::value::Double(RAD));
        MicroMeteo->putAttribute("TT", new vle::value::Double(TT));
        
        std::cout << "\n\n";
        outputs.push_back( MicroMeteo ); 

    }


    /*************************************************************************/
    virtual vd::Time timeAdvance() const
    {
        //std::cout << "-----------------------------------------------" << "\n";
        //std::cout << "----- " << p_model_name << " timeAdvance -----------------\n";
        // std::cout << p_model_name << ".timeAdvance \n";
        //std::cout << "\n\n";
        return vd::Time(p_delay);
    }

    /*************************************************************************/
    virtual void internalTransition(const vd::Time& time)
    {

        /* determine (incremente) m_choix */
        m_choix++;

        /* traitement des donnees */
        RAD++;
        TT = TT + 10;
        // ...
    }

    /*************************************************************************/
    /**
	 * Lit evenement(s) recus
	 */
    virtual void externalTransition(const vd::ExternalEventList& events,
                                    const vd::Time& time)
    {

    }

    /*************************************************************************/
    virtual void confluentTransitions(const vd::Time& time,
                                      const vd::ExternalEventList& events)
    {
        //std::cout << "\n" << "------------------------------ ";
        //std::cout << p_model_name << ".confluentTransitions \n";

        internalTransition(time);
        externalTransition(events, time);
    }

    /*************************************************************************/
    virtual vv::Value* observation(const vd::ObservationEvent& events ) const
    {
        //std::cout << "-----------------------------------------------" << "\n";
        //std::cout << "----- " << p_model_name << " observation -----------------\n";
        //std::cout << "\n\n";
        if ( events.onPort("m_choix") ){
            return buildInteger(m_choix);
        } else if (events.onPort("RAD")){
            return buildDouble(RAD);       
        } else if (events.onPort("TT")){
            return buildDouble(TT);
        } else { 
        return 0;}
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
        double RAD;
        double TT;

};

} // namespace pydynamics

DECLARE_DYNAMICS(pydynamics::PseudoMeteo)

