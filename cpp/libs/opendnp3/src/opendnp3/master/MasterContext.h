/**
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
#ifndef OPENDNP3_MASTERCONTEXT_H
#define OPENDNP3_MASTERCONTEXT_H

#include "opendnp3/LayerInterfaces.h"

#include <openpal/executor/IExecutor.h>
#include <openpal/logging/LogRoot.h>
#include <openpal/container/Queue.h>
#include <openpal/container/DynamicBuffer.h>

#include "opendnp3/master/MasterScheduler.h"
#include "opendnp3/master/IMasterState.h"
#include "opendnp3/master/ITaskLock.h"
#include "opendnp3/master/IMasterApplication.h"

#include <deque>

namespace opendnp3
{

class MasterContext : public ICommandProcessor, public IScheduleCallback
{
	public:	

	MasterContext(	openpal::IExecutor& executor,
					openpal::LogRoot& root, 
					ILowerLayer& lower,
					ISOEHandler& SOEHandler,					
					opendnp3::IMasterApplication& application,
					const MasterParams& params,
					ITaskLock& taskLock
				);
	
	openpal::Logger logger;
	openpal::IExecutor* pExecutor;
	ILowerLayer* pLower;

	// ------- configuration --------
	MasterParams params;
	ISOEHandler* pSOEHandler;
	ITaskLock* pTaskLock;
	opendnp3::IMasterApplication* pApplication;

	// ------- dynamic state ---------
	bool isOnline;
	bool isSending;
	uint8_t solSeq;
	uint8_t unsolSeq;
	IMasterTask* pActiveTask;
	IMasterState* pState;
	openpal::ITimer* pResponseTimer;
	MasterTasks staticTasks;
	MasterScheduler scheduler;

	std::deque<APDUHeader> confirmQueue;
	

	openpal::DynamicBuffer txBuffer;
	
	void PostCheckForTask();

	// ------- external events ----------
	bool OnLayerUp();
	bool OnLayerDown();
	void OnSendResult(bool isSucccess);
	void OnReceive(const openpal::ReadOnlyBuffer& apdu);

	// ------- internal events -------
	
	void OnUnsolicitedResponse(const APDUResponseHeader& response, const openpal::ReadOnlyBuffer& objects);
	void OnReceiveIIN(const IINField& iin);

	// ------- command events ----------

	virtual void SelectAndOperate(const ControlRelayOutputBlock& command, uint16_t index, ICommandCallback& callback) override final;
	virtual void DirectOperate(const ControlRelayOutputBlock& command, uint16_t index, ICommandCallback& callback) override final;

	virtual void SelectAndOperate(const AnalogOutputInt16& command, uint16_t index, ICommandCallback& callback) override final;
	virtual void DirectOperate(const AnalogOutputInt16& command, uint16_t index, ICommandCallback& callback) override final;

	virtual void SelectAndOperate(const AnalogOutputInt32& command, uint16_t index, ICommandCallback& callback) override final;
	virtual void DirectOperate(const AnalogOutputInt32& command, uint16_t index, ICommandCallback& callback) override final;

	virtual void SelectAndOperate(const AnalogOutputFloat32& command, uint16_t index, ICommandCallback& callback) override final;
	virtual void DirectOperate(const AnalogOutputFloat32& command, uint16_t index, ICommandCallback& callback) override final;

	virtual void SelectAndOperate(const AnalogOutputDouble64& command, uint16_t index, ICommandCallback& callback) override final;
	virtual void DirectOperate(const AnalogOutputDouble64& command, uint16_t index, ICommandCallback& callback) override final;

	// ----- Helpers accessible by the state objects -----
	void StartTask(IMasterTask* pTask);
	bool CancelResponseTimer();
	void QueueConfirm(const APDUHeader& header);
	void StartResponseTimer();	

	private:
	
	// callback from the scheduler that a task is ready to run	
	virtual void OnPendingTask() override final;

	void QueueUserTask(const openpal::Function0<IMasterTask*>& action);

	void OnResponseTimeout();

	void CheckForTask();	

	// -------- helpers --------

	bool CheckConfirmTransmit();

	void Transmit(const openpal::ReadOnlyBuffer& output);	

	template <class T>
	void SelectAndOperateT(const T& command, uint16_t index, ICommandCallback& callback);

	template <class T>
	void DirectOperateT(const T& command, uint16_t index, ICommandCallback& callback);
};

template <class T>
void MasterContext::SelectAndOperateT(const T& command, uint16_t index, ICommandCallback& callback)
{
	if (isOnline)
	{
		// TODO create a dynamically allocated command task and queue it on the scheduler
		callback.OnComplete(CommandResponse(CommandResult::NO_COMMS));		
	}
	else
	{
		callback.OnComplete(CommandResponse(CommandResult::NO_COMMS));
	}

	
}

template <class T>
void MasterContext::DirectOperateT(const T& command, uint16_t index, ICommandCallback& callback)
{
	if (isOnline)
	{		
		// TODO create a dynamically allocated command task and queue it on the scheduler
		callback.OnComplete(CommandResponse(CommandResult::NO_COMMS));
	}
	else
	{
		callback.OnComplete(CommandResponse(CommandResult::NO_COMMS));
	}
}

}

#endif
