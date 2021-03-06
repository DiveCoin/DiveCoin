// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0x02;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("04c5788ca1e268a7474763fa965210b6fa6b04a45f52d21056c62fb19a2de991aa15aa1d1c516f34d2a0016f51a87959c89f51a148db30c839f71bc525dde8c480");
        nDefaultPort = 47680;
        nRPCPort = 47685;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 100000; // 2 years

        // Genesis block
        const char* pszTimestamp = "Dive, Dive, Dive, Bro.";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 16 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04becedf6ebadd4596964d890f677f8d2e74fdcc313c6416434384a66d6d8758d1c92de272dc6713e4a81d98841dfdfdc95e204ba915447d2fe9313435c78af3e8") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1507063100;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 962023;

        hashGenesisBlock = genesis.GetHash();
		
        /*while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        printf("%x\n", bnProofOfWorkLimit.GetCompact());
        genesis.print();*/

        assert(hashGenesisBlock == uint256("0x0000007ebb7540be0e08f1986f848972f0fd49ba9d3d70e119575ac4259aa10c"));
        assert(genesis.hashMerkleRoot == uint256("0x2e40555def030a0055b5a5ada5a0503676024540d1e632c804f48cdbbb048cb2"));

        vSeeds.push_back(CDNSSeedData("165.227.0.203", "165.227.0.203"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,204); 

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0x02;
		
        vAlertPubKey = ParseHex("040d3090a194381599d0f53f89ec60b9ec77f0e7b61978ef445142c8a4f1e154ca3441a5e46e12910540352edbd8af43fc1ee1da9a935c1c252fe7426c323d3d32");
		
        nDefaultPort = 21994;
        nRPCPort = 21995;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1388868139;
        genesis.nNonce = 423087994;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000082f5939c2154dbcba35f784530d12e9d72472fcfaf29674ea312cdf4c83"));

        vFixedSeeds.clear();
        vSeeds.clear();

       /* base58Prefixes[PUBKEY_ADDRESS] = {80};                     // Testnet divecoin addresses start with 'x' or 'y'
		base58Prefixes[SCRIPT_ADDRESS] = {44};                     // Testnet divecoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY]     = {88+128};                 // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0}; // Testnet divecoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37}; // Testnet divecoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_COIN_TYPE]  = {0x80000001}.convert_to_container<std::vector<unsigned char> >();  */           // Testnet divecoin BIP44 coin type is '5' (All coin's testnet default)
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x56;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        nDefaultPort = 18444;
        strDataDir = "regtest";

        hashGenesisBlock = genesis.GetHash();
        // assert(hashGenesisBlock == uint256("0x000008ca1832a4baf228eb1553c03d3a2c8e02399550dd6ea8d65cec3ef23d2e"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
