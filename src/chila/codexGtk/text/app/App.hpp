/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP__APP_HPP
#define CHILA_CODEX_TEXT_APP__APP_HPP

#include "impl/connection/CPerformerData.hpp"
#include "impl/connection/TextEditor.hpp"
#include "../lib/fwd.hpp"
#include "macros.fgen.hpp"

MY_NSP_START
{
    class App
    {
        public:
            App();
            void connect(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher, bool preLoaderConnect);
            void start();

        private:
            using CPModTypes = impl::connection::CPerformerData::ModuleTypes;

            struct Providers
            {
                CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPED_INSTANCES(CPModTypes, CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_SEQ)
            } providers;

            bool showArguments;
            bfs::path installDir;
            Glib::RefPtr<Gtk::Builder> builder;

            template <typename Provider>
            void addConnectorFunctions(Provider &provider);

            lib::ColorMap loadHighlightColors();
            lib::ExtensionFTypeMap loadExtensionFTypeMap();
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
