/* SockAPI.hpp
 * -----------------------------------------------------------------------------
 * Copyright (C) 2015 George Mitchell
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCKAPI_H
#define SOCKAPI_H

#include <string>
#include <vector>
#include <numeric>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class API
{
public:
    static const std::vector<std::string> API_CALLS;

    enum API_CALL { ReadTemp, AddSchedule, RemoveSchedule, ShouldRunHeat, ShouldRunAC, ShouldRunFan,
        TargetTemp, EnableFan, DisableFan, PrintSchedule };

    API(bool isServer);
    ~API();
    bool CallFunction(API_CALL call, void* adtlData, size_t dataLen, void* buffer, size_t len);
    bool CallFunction(API_CALL call);

    void CallbackWrapper();
    virtual void Callback(API_CALL call, const void *rcvData, const size_t rcvDataLen, void *&sendData, int *sendDataLen);

    template<typename ret, typename... Args>
    ret t_func(API_CALL call, Args... adtlargs)
    {
        const unsigned short int nArgs = sizeof...(adtlargs);
        ret returnVal = 0;

        std::vector<const char*> params = {(const char*)&adtlargs...};
        std::vector<size_t> paramSizes = {sizeof(adtlargs)...};

        size_t dataSize = std::accumulate(paramSizes.begin(), paramSizes.end(), 0);
        char *data = (char*)malloc(sizeof(char) * dataSize);
        size_t position = 0;
        for (size_t i = 0; i < nArgs; ++i)
        {
            std::memcpy(data + position, params[i], paramSizes[i]);
            position += paramSizes[i];
        }

        CallFunction(call, data, dataSize, &returnVal, sizeof(ret));

        delete data;
        return returnVal; 
    }

    //template<typename ret, typename... Args>
    //ret t_func(API_CALL call, Args... adtlargs);
    
private:
    int sock_;
    bool isServer_;
};

#endif

