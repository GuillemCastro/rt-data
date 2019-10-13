/**
 * rt-data
 * Copyright (C) 2019 Guillem Castro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "HTTPWriter.h"

std::atomic<bool> HTTPWriter::curl_init(false);
std::atomic<unsigned int> HTTPWriter::curl_count(0);

void HTTPWriter::open() {
    if (!curl_init) {
        curl_global_init(CURL_GLOBAL_ALL);
        curl_init = true;
    }
    curl_count++;
    isopen = true;
}

void HTTPWriter::write(std::shared_ptr<Data> data) {
    write("default", data);
}

void HTTPWriter::write(std::string topic, std::shared_ptr<Data> data) {
    std::unique_lock<std::mutex> lck(mtx);
    CURL* curl = curl_easy_init();
    curl_slist *hs=NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");
    if (curl == NULL) {
        throw std::runtime_error("Error initializing cURL");
    }
    JSONObject json(topic);
    data->serialize(&json);
    nlohmann::json post_body = json.get_JSON();
    std::string post_body_str = post_body.dump();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_body_str.c_str());
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
}

void HTTPWriter::close() {
    curl_count--;
    if (curl_init && curl_count == 0) {
        curl_global_cleanup();
        curl_init = false;
    }
    isopen = false;
}

bool HTTPWriter::is_open() {
    return curl_init && isopen;
}

bool HTTPWriter::is_closed() {
    return !curl_init || !isopen;
}

void HTTPWriter::flush() {

}