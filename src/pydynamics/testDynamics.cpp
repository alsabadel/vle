#include "testDynamics.hpp"

#include <vle/devs/ExternalEvent.hpp>
//#include <vle/devs/Dynamics.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Integer.hpp>
#include <vle/value/Boolean.hpp>
#include <vle/value/String.hpp>
#include <vle/utils/Path.hpp>
#include <vle/utils/Package.hpp>

//using namespace vle;

namespace vle { namespace devs {

	ExternalEvent* Dynamics::buildEvent(const std::string& portName) const
	{
	  return new ExternalEvent(portName);
	}

	ExternalEvent* Dynamics::buildEventWithADouble(
	    const std::string & portName,
	    const std::string & attributeName,
	    double attributeValue) const
	{
	    ExternalEvent* event = new ExternalEvent(portName);
	    event->putAttribute(attributeName,
		                value::Double::create(attributeValue));
	    return event;
	}

	ExternalEvent* Dynamics::buildEventWithAInteger(
	    const std::string & portName,
	    const std::string & attributeName,
	    long attributeValue) const
	{
	    ExternalEvent* event = new ExternalEvent(portName);

	    event->putAttribute(attributeName,
		                  value::Integer::create(attributeValue));
	    return event;
	}

	ExternalEvent* Dynamics::buildEventWithABoolean(
	    const std::string & portName,
	    const std::string & attributeName,
	    bool attributeValue) const
	{
	    ExternalEvent* event = new ExternalEvent(portName);

	    event->putAttribute(attributeName,
		                value::Boolean::create(attributeValue));
	    return event;
	}

	ExternalEvent* Dynamics::buildEventWithAString(
	    const std::string & portName,
	    const std::string & attributeName,
	    const std::string & attributeValue) const
	{
	    ExternalEvent* event = new ExternalEvent(portName);

	    event->putAttribute(attributeName,
		                value::String::create(attributeValue));
	    return event;
	}


	std::string Dynamics::getPackageDir() const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getDir(vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}


	std::string Dynamics::getPackageSimulatorDir() const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getPluginSimulatorDir(vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}


	std::string Dynamics::getPackageSrcDir() const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getSrcDir(vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageDataDir() const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getDataDir(vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageDocDir() const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getDocDir(vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageExpDir() const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getExpDir(vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageFile(const std::string& name) const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getFile(name, vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageLibFile(const std::string& name) const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getLibFile(name, vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageSrcFile(const std::string& name) const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getSrcFile(name, vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageDataFile(const std::string& name) const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getDataFile(name, vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageDocFile(const std::string& name) const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getDocFile(name, vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}

	std::string Dynamics::getPackageExpFile(const std::string& name) const
	{
	    vle::utils::Package pkg(*m_packageid);
	    if (pkg.existsBinary()) {
		return pkg.getExpFile(name, vle::utils::PKG_BINARY);
	    } else {
		throw vle::utils::FileError(vle::fmt(_("Package '%1%' is not "
		        "installed")) % *m_packageid);
	    }
	}
	
	int b(int i)
	{
	    return i+2;
	};

}} //namespace vle
