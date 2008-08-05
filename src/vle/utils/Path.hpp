/**
 * @file src/vle/utils/Path.hpp
 * @author The VLE Development Team
 */

/*
 * VLE Environment - the multimodeling and simulation environment
 * This file is a part of the VLE environment (http://vle.univ-littoral.fr)
 * Copyright (C) 2003 - 2008 The VLE Development Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */




#ifndef VLE_UTILS_PATH_HPP
#define VLE_UTILS_PATH_HPP

#include <string>
#include <list>
#include <glibmm/fileutils.h>


namespace vle { namespace utils {

    /**
     * @brief Portable way, i.e. Linux/Unix/Windows to get VLE paths. Linux
     * and Unix versions use compiled paths introduced by installer, Windows
     * version use Registry to store his paths. This class is a singleton.
     * Three environment variables are used to store another paths.
     * VLE_SIMULATOR_PATH, VLE_OOV_PATH and VLE_MODEL_PATH.
     *
     * To use it:
     * @code
     * std::string binpath(utils::Path::path()->getDefaultBinDir());
     * @endcode
     */
    class Path
    {
    public:
        /**
         * @brief Define a list of directories.
         */
        typedef std::list < std::string > PathList;

        /**
         * @brief Return the prefix of the compilation on Unix or installation
         * on Windows.
         * @return A string path.
         */
        const std::string& getPrefixDir() const;

        std::string getPixmapsDir() const;

        std::string getGladeDir() const;

        std::string getPixmapsFile(const std::string& file) const;

        std::string getGladeFile(const std::string& file) const;

        std::string getHomeDir() const;

        /**
         * @brief Get the list of simulator's directories.
         * @return A list of directory name.
         */
        inline const PathList& getSimulatorDirs() const
        { return m_simulator; }

        /**
         * @brief Get the list of stream's directories.
         * @return A list of directory name.
         */
        inline const PathList& getStreamDirs() const
        { return m_stream; }

        /**
         * @brief Get the list of model's directories.
         * @return A list of directory name.
         */
        inline const PathList& getModelDirs() const
        { return m_model; }

        void addSimulatorDir(const std::string& dirname);

        void addStreamDir(const std::string& dirname);

        void addModelDir(const std::string& dirname);

        void addPluginDir(const std::string& dirname);

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *
         * Manage singleton
         *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        /**
         * @brief Return a Path object instantiate in singleton method.
         * @return A reference to the singleton object.
         */
        inline static Path& path()
        { if (mPath == 0) mPath = new Path; return *mPath; }

        /**
         * @brief Delete Path object instantiate from function path().
         */
        inline static void kill()
        { delete mPath; mPath = 0; }

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *
         * Static function to easily use the utils::Path class.
         *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        /**
         * @brief Build a string path based on the concatenation of install
         * prefix and the provided buffer. For instance, if cmake was called
         * with CMAKE_INSTALL_PREFIX=$HOME/usr on Unix, this function returns
         * $HOME/usr/buffer.
         * @param buf The buffer to concatenate to the install prefix.
         * @return A string path.
         */
        static std::string buildPrefixPath(const std::string& buf);

        /**
         * @brief Build a string path based on the concatenation of install
         * prefix, library dir and provided buffer. For instance:
         * @code
         * buildPrefixLibrariesPath("/home/toto/usr", "simulator");
         * // /home/toto/usr/lib/vle-0.5.0/simulator on Unix
         * buildPrefixLibrariesPath("c:\\program files\vle", "simulator");
         * // c:\program files\vle\lib\vle-0.5.0\simulator on Win32
         * @endcode
         * @param prefix the prefix of the path.
         * @param buf the buffer to concatenate to the install prefix.
         * @return A string path.
         */
        static std::string buildPrefixLibrariesPath(const std::string& prefix,
                                                    const std::string& buf);

        /**
         * @brief Build a string path based on the concatenation of install
         * prefix, share prefix dir and provided program name and buffer. For
         * instance:
         * @code
         * buildPrefixSharePath("/home/toto/usr", "vle", "pixmaps");
         * // /home/toto/usr/share/vle-0.5.0/vle/pixmaps on Unix
         * buildPrefixSharePath("c:\\program files\vle", "vle", "pixmaps");
         * // c:\program files\vle\share\vle-0.5.0\vle\pixmaps on Win32
         * @endcode
         * @param prefix the prefix of the path.
         * @param prg A buffer to concatenate.
         * @param name A buffer to concatenante
         * @return A string path.
         */
        static std::string buildPrefixSharePath(const std::string& prefix,
                                                const std::string& prg,
                                                const std::string& name =
                                                std::string());

        /**
         * @brief Build a path using two string.
         * For instance:
         * @code
         * std::string s = utils::Path::buildPath("home", "vle");
         * // Returns "home/vle" on Unix or "home\\vle" on Win32.
         * @endcode
         * @param left the string dirname.
         * @param right the string dirname.
         * @return the build path of left and right strings using the good
         * separator.
         */
        static std::string buildPath(const std::string& left,
                                     const std::string& right);

        /**
         * @brief Build a path from user home directory to specified dir. The
         * fallowing example return the string "/home/<user>/.vle/model".
         * @code
         * std::string s = utils::Path::buildUserPath("model");
         * // s == /home/gauthier/.vle/model on unix with my nickname.
         * // s == c:\Documents and Settings\gauthier\My documents on win32.
         * @endcode
         * @param dir the directory to found into the user home dir.
         * @return a concatenation of user home dir and specified directory.
         */
        static std::string buildUserPath(const std::string& dir =
                                           std::string());

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *
         * Functor
         *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        /**
         * @brief Predicate functor to test the existence of a directory.
         */
        struct IsDirectory
            : public std::unary_function < std::string, bool >
        {
            /**
             * @brief Check if the directory exits.
             * @param the string to check.
             * @return true if the directory exists, false otherwise.
             */
            bool operator()(const std::string& dirname) const
            {
                return Glib::file_test(dirname, Glib::FILE_TEST_EXISTS |
                                       Glib::FILE_TEST_IS_DIR);
            }
        };

        /**
         * @brief Check if the directory exists.
         * @param dirname the directory to check.
         * @return true if str is a directory.
         */
        bool static isDirectory(const std::string& dirname)
        {
            return Glib::file_test(dirname, Glib::FILE_TEST_EXISTS |
                                   Glib::FILE_TEST_IS_DIR);
        }

    private:
        PathList    m_simulator;
        PathList    m_stream;
        PathList    m_model;
        std::string m_prefix;

        /**
         * @brief A default constructor that call the initPath member.
         * @throw utils::InternalError if Initialisation of the class failed.
         */
        Path();

        /**
         * @brief Build the paths. This function exist in two part of the file,
         * on for Unix/Linux another for Windows for registry access.
         * @return true if success, false otherwise.
         */
        bool initPath();

        /**
         * @brief Build the paths from environment variables.
         * @param variable The name of the variable to read.
         * @param out The output parameter to store valid path.
         * @return true if success, false if variable does not exist.
         */
        bool readEnv(const std::string& variable, PathList& out);

        static Path* mPath; /// The static Path for singleton design pattern.
    };

}} // namespace vle utils

#endif
