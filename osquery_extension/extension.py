#!/usr/bin/env python3
import json
import osquery
from os.path import expanduser

@osquery.register_plugin
class vimPlugins(osquery.TablePlugin):
    def name(self):
        return "vimplugins"
    def columns(self):
        return [
            osquery.TableColumn(name="Plugin Name", type=osquery.STRING),
            osquery.TableColumn(name="Github Stars", type=osquery.STRING),
            osquery.TableColumn(name="VimAwesome Category", type=osquery.STRING),
            osquery.TableColumn(name="Open Issues", type=osquery.STRING),
            osquery.TableColumn(name="Closed Issues", type=osquery.STRING),
        ]
    def generate(self, context):
        query_data = []
        home = expanduser("~")
        input_file = open(home + '/.vim-info/vimPlugins.json')
        json_array = json.load(input_file)
        for item in json_array:
            row = {}
            row["Plugin Name"] = item['name']
            row["Github Stars"] = item['stars']
            row["VimAwesome Category"] = item['category']
            row["Open Issues"] = item['open']
            row["Closed Issues"] = item['closed']
            query_data.append(row)
        return query_data

@osquery.register_plugin
class vimRunTime(osquery.TablePlugin):
    def name(self):
        return "vimruntime"
    def columns(self):
        return [
                osquery.TableColumn(name="RunTime in Sec", type=osquery.STRING),
                osquery.TableColumn(name="RunTime in MS", type=osquery.STRING),
        ]
    def generate(self, context):
        query_data = []
        home = expanduser("~")
        input_file = open(home + '/.vim-info/vimRunTime.json')
        json_obj = json.load(input_file)
        row = {}
        row["RunTime in Sec"] = json_obj['runtime_s']
        row["RunTime in MS"] = json_obj['runtime_ms']
        query_data.append(row)
        return query_data

@osquery.register_plugin
class vimInfoData(osquery.TablePlugin):
    def name(self):
        return "viminfodata"
    def columns(self):
        return [
                osquery.TableColumn(name="Config File", type=osquery.STRING),
                osquery.TableColumn(name="Plugin Manager", type=osquery.STRING),
                osquery.TableColumn(name="Plugins Count", type=osquery.STRING),
                osquery.TableColumn(name="Extension Socket", type=osquery.STRING),
        ]
    def generate(self, context):
        query_data = []
        home = expanduser("~")
        input_file = open(home + '/.vim-info/vimInfo.json')
        json_obj = json.load(input_file)
        row = {}
        row["Config File"] = json_obj['config_file']
        row["Plugin Manager"] = json_obj['plugin_manager']
        row["Plugins Count"] = json_obj['plugins_count']
        row["Extension Socket"] = json_obj['socket']
        query_data.append(row);
        return query_data;
if __name__ == "__main__":
    osquery.start_extension(name="vim_info", version="1.0.0")
