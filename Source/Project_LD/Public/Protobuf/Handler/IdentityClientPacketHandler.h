// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include <IdentityPacket.pb.h>
//#include <Network/SendBuffer.h>
//#include <Network/RecvBuffer.h>
//#include <Network/NetworkController.h>
//#include <Containers/Array.h>
//
//class ANetworkController;
//
//using SendBufferPtr = TSharedPtr<class FSendBuffer>;
//static TArray<TFunction<bool(ANetworkController*, BYTE*, int32)>> GPacketHandler;
//
//enum class EPakcetID : uint16
//{
//	C2S_Singin = 1000,
//	S2C_Singin = 1001,
//	C2S_Singup = 1002,
//	S2C_Singup = 1003,
//	C2S_EmailVerified = 1004,
//	S2C_EmailVerified = 1005,
//};
//
//// Custom Handlers
//bool Handle_INVALID(ANetworkController* session, BYTE* buffer, int32 len);
//bool Handle_S2C_Singin(ANetworkController* session, Protocol::S2C_Singin& pkt);
//bool Handle_S2C_Singup(ANetworkController* session, Protocol::S2C_Singup& pkt);
//bool Handle_S2C_EmailVerified(ANetworkController* session, Protocol::S2C_EmailVerified& pkt);
//
///**
// * 
// */
//class PROJECT_LD_API FIdentityClientPacketHandler
//{
//
//public:
//	static void Init()
//	{
//		GPacketHandler.Init(Handle_INVALID, 1024);
//
//		//for (int32 i = 0; i < UINT16_MAX; i++)
//		//	GPacketHandler[i] = Handle_INVALID;
//
//		GPacketHandler[static_cast<uint16>(EPakcetID::S2C_Singin)] = [](ANetworkController* session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S2C_Singin>(Handle_S2C_Singin, session, buffer, len); };
//		GPacketHandler[static_cast<uint16>(EPakcetID::S2C_Singup)] = [](ANetworkController* session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S2C_Singup>(Handle_S2C_Singup, session, buffer, len); };
//		GPacketHandler[static_cast<uint16>(EPakcetID::S2C_EmailVerified)] = [](ANetworkController* session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S2C_EmailVerified>(Handle_S2C_EmailVerified, session, buffer, len); };
//	}
//
//	static bool HandlePacket(ANetworkController* session, BYTE* buffer, int32 len)
//	{
//		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
//		return GPacketHandler[header->id](session, buffer, len);
//	}
//	static SendBufferPtr MakeSendBuffer(ANetworkController* session, Protocol::C2S_Singin& pkt) { return MakeSendBuffer(session, pkt, static_cast<uint16>(EPakcetID::C2S_Singin)); }
//	static SendBufferPtr MakeSendBuffer(ANetworkController* session, Protocol::C2S_Singup& pkt) { return MakeSendBuffer(session, pkt, static_cast<uint16>(EPakcetID::C2S_Singup)); }
//	static SendBufferPtr MakeSendBuffer(ANetworkController* session, Protocol::C2S_EmailVerified& pkt) { return MakeSendBuffer(session, pkt, static_cast<uint16>(EPakcetID::C2S_EmailVerified)); }
//
//private:
//	template<typename PacketType, typename ProcessFunc>
//	static bool HandlePacket(ProcessFunc func, ANetworkController* session, BYTE* buffer, int32 len)
//	{
//		
//		PacketType pkt;
//		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
//			return false;
//
//		return func(session, pkt);
//	}
//
//	template<typename T>
//	static SendBufferPtr MakeSendBuffer(ANetworkController* session, T& pkt, uint16 pktId)
//	{
//		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
//		const uint16 packetSize = dataSize + sizeof(PacketHeader);
//
//		SendBufferPtr SendBuffer = MakeShared<FSendBuffer>(packetSize);
//		PacketHeader* header = reinterpret_cast<PacketHeader*>(SendBuffer->GetData());
//		header->size = packetSize;
//		header->id = pktId;
//		pkt.SerializeToArray(&header[1], dataSize);
//		return SendBuffer;
//	}
//};
