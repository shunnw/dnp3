/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */

#include "asiodnp3/DefaultListenCallbacks.h"

namespace asiodnp3
{

DefaultListenCallbacks::DefaultListenCallbacks()
{}

	
bool DefaultListenCallbacks::AcceptConnection(uint64_t sessionid, const std::string& ipaddress)
{		
	return true;
}

openpal::TimeDuration DefaultListenCallbacks::GetFirstFrameTimeout()
{
	return openpal::TimeDuration::Seconds(30);
}

void DefaultListenCallbacks::OnFirstFrame(uint64_t sessionid, const opendnp3::LinkHeaderFields& header, ISessionAcceptor& acceptor)
{			
	opendnp3::MasterStackConfig config;
		
	// full implementations will look up config information for the SRC address

	config.link.LocalAddr = header.dest;
	config.link.RemoteAddr = header.src;

	auto soe = std::make_shared<PrintingSOEHandler>();
	auto app = std::make_shared<DefaultMasterApplication>();

	// full implementations will keep a std::shared_ptr<IGPRSMaster> somewhere			
	auto master = acceptor.AcceptSession(SessionIdToString(sessionid), soe, app, config);
}

void DefaultListenCallbacks::OnSessionClose(uint64_t sessionid, std::shared_ptr<IMasterSession> session)
{
	std::cout << "Session close: " << sessionid << std::endl;
	// full implementations would drop any references they're holding to this session
	// shared_ptr can be used with == operator also
}

std::string DefaultListenCallbacks::SessionIdToString(uint64_t id)
{	
	std::ostringstream oss;
	oss << "session-" << id;	
	return oss.str();
}

}



