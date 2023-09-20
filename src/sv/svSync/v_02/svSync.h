//  *******************************************************************************
//  
//  mpfw / fw2 - Multi Platform FirmWare FrameWork 
//      library that contains the essential code that is used in every application
//  Copyright (C) (2023) Marco Dau
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  
//  You can contact me by the following email address
//  marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
//  
//  *******************************************************************************
/*
 * svSync.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Marco Dau
 *
 
	Description:
		this service executes a method/function (passed during its construction step) in a determined thread following a request of a process
		that runs in a different thread. The method/function that is object of the present description must be performed in a specific thread
		because handles a common resources shared between different processes run in different thread.
		The rs232/rs484 channel might be an example.

		questa classe può essere usata in questo contesto:
		sono presenti:
		- una macchina a stati i cui handler associati agli stati possono essere eseguiti in thread differenti
		- un altro processo X desidera cambiare lo stato di questa macchina a stati
		. se il processo gira in un thread differente da quello in cui sta girando lo stato attivo della macchina a stati
		  si ha una race-condition perchè ci sono due processi che girano in differenti thread che potenzialmente
		  possono scrivere su una stessa locazione di memoria
		. questa classe fornisce un servizio che permette al processo X di cambiare lo stato di una macchina a stati
		  senza generare una race-condition
			. questa cosa viene fatta semplicemente inviando un segnale/comando da un thread ad un altro 
		      in particolare da un thread X qualunque al thread, in quel momento, "possessore", della risorsa in modo che quest'ultimo
			  si occupi dell'operazione di modifica
			. quindi la funzione "UpdateSyncResorces" messa a disposizione dalla presente classe 
				. che esegue una funzione che modificherà delle locazioni di memoria che già sono gestite dallo stato attivo 
				  della macchina a stati presa ad esempio
				. va eseguita nello stesso thread in cui sta girando lo stato attivo della macchina a stati presa ad esempio
				  dato che scriverà sulle stesse locazioni di memoria in uso da quest'ultimo
	
	Test description:
		il test ha bisogno di definire degli stati e quindi fa uso della classe svState
		- ci saranno due stati che ripetutamente richiederanno una scrittura su una memoria condivisa con un altro stato
		- ci sarà uno stato che ripetutamente controlla se tra due letture consecutive eventualmente intramezzate da 
		  un loop di ritardo avviene una scrittura
			  
	. la classe dovrebbe avere anche due parametri che indicano il thread in cui viene impostata la richiesta
	  ed il thread dove viene eseguita l'istruzione richiesta
	. inoltre se il thread in cui viene eseguita la richiesta può essere cambiato dinamicamente
	. non credo sia possibile cambiare dinamicamante il thread in cui viene impostata la richiesta
	  . questo thread non può essere controllato a priori
	
	. Issue: quando ci sono più thread che contemporaneamente fanno richieste diverse
	         o anche stesse richieste ma con parametri diversi
		. Possibili risoluzioni
			. tenere traccia del thread per cui viene eseguita la richiesta
				. ogni thread ha un suo comando
			. il comando successivo non verrà eseguito finchè non è stato fatto
			  il reset da parte del thread richiedente
			. avere un istanza della classe svSync per ogni processo thread richiedente
			. non permettere che siano presenti richieste contemporanee
	. considerazione:
		. la funzione handler/"UpdateSyncResorces" non verrà mai eseguita contemporaneamente in più thread
			. se questo fosse vero
				. si puo eliminare l'array "g_ArrayWrt" e considerare una singola variabile
				. oppure tutti gli elementi dell'array "g_ArrayWrt" possono essere modificati
					. dunque tenendo traccia del comando e del thread richidente
					. questo però richiede che la funzione di reset "ResetSyncSignals" venga eseguita nello stesso
					  thread della funzione "UpdateSyncResorces"
					  	. per superare questo problema si può imporre di eseguire la funzione di reset prima
						  della funzione "handler"

 */

#ifndef SV_SYNC_H_
#define SV_SYNC_H_

// system include
#include <atomic>
#include <array>
#include <cstdint>

// lib include
#include <cg_krThread.h>

#define MAKE_svSyncSgn(group, code) ((((svSync::k_svSyncSgn_END) + (group)*20) + (code)))

namespace fw2 { namespace core { namespace core {

class svSync {
public:

	enum k_svSyncSgn {
		 k_svSyncSgn_NULL
		,k_svSyncSgn_END
	};

	// ************* TYPEDEF ******************************
	typedef uint8_t sync_sgn_t;	// synchronization SiGNal
	typedef uint8_t sync_val_t;	// VALue/parameter to assign to the synchronized resource
	typedef void (*SyncResourcesHandler_t)	(krThreadId, sync_sgn_t, sync_val_t);
	// ************* END TYPEDEF **************************

	// constructor
	svSync(SyncResourcesHandler_t				);
	svSync(SyncResourcesHandler_t	,krThreadId	);

	// ************************
	// uni-thread section - START
	// 
	// the following member CAN'T / MUSTN'T be 
	// . called (in case of method/handler) or 
	// . writen (in case of variable)
	// from more than one thread at the same time
	// 
	SyncResourcesHandler_t	g_Handler;									// ONLY one thread at a time can call it
	krThreadId				g_ThreadId;
	std::array<uint8_t, krThread_Num> g_ArrayWrt;						// ONLY one thread at a time can write every element of it

	void UpdateSyncResorces	(krThreadId, sync_val_t 			);		// ONLY one thread at a time can call it
	//
	// uni-thread section - END
	// ________________________

	// ************************
	// multi-thread section - START
	//
	// the following member may be 
	// . called (in case of method/handler) or 
	// . written (in case of variable)
	// by more than one thread at the same time
	// provided that 
	std::array<uint8_t, krThread_Num> g_ArrayRdr;						// every element is linked to one exact thread, and ONLY that thread can modify it
	std::array<uint8_t, krThread_Num> g_ArrayPar;						// every element is linked to one exact thread, and ONLY that thread can modify it

	void ResetSyncSignals	(krThreadId							);		// EVERY thread can call it at the same time
	uint8_t Send			(krThreadId, sync_sgn_t				);		// EVERY thread can call it at the same time
	uint8_t Send			(krThreadId, sync_sgn_t, sync_val_t	);		// EVERY thread can call it at the same time
	//
	// multi-thread section - END
	// ________________________
};

} } }	// namespace fw2::core::core


#endif /* SV_SYNC_H_ */
