// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

//using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x05;
        pchMessageStart[1] = 0x22;
        pchMessageStart[2] = 0x53;
        pchMessageStart[3] = 0x07;
	vAlertPubKey = ParseHex("041cb997e1222cc7c008b5354714c7cdd846eb4337a7039c0900972aa36cf3999ba3060eff592d29919ee65946c0ccab37f03bd766e916813af50dd80585d9ef88");
        nDefaultPort = 11517;
        nRPCPort = 17515;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
	// CBlock(hash=000009b88ae01c8e009d08651c904a1b00f9e24d72538f49c242ba2ee14d859a, ver=1, pow_hash=000009b88ae01c8e009d08651c904a1b00f9e24d72538f49c242ba2ee14d859a, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199185, nBits=1e0fffff, nNonce=921682, vtx=1)
  	//  Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//   CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//   CTxOut(empty)
  	//  vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        const char* pszTimestamp = "GreenCoinV2 Launches.";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1393221600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1450199185;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 921682;
	hashGenesisBlock = genesis.GetHash();
	nLastPoWBlock    = 2160;
        assert(hashGenesisBlock == uint256("0x000009b88ae01c8e009d08651c904a1b00f9e24d72538f49c242ba2ee14d859a"));
        assert(genesis.hashMerkleRoot == uint256("0xf13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4"));

	vSeeds.push_back(CDNSSeedData("81.83.209.224", "81.83.209.224"));
	vSeeds.push_back(CDNSSeedData("67.161.120.48", "67.161.120.48"));
	vSeeds.push_back(CDNSSeedData("73.12.235.88", "73.12.235.88"));
	vSeeds.push_back(CDNSSeedData("174.31.114.98", "174.31.114.98"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,  38);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,  85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,  166);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
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
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0x0c;
        pchMessageStart[2] = 0x2f;
        pchMessageStart[3] = 0xdc;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 25713;
        nRPCPort = 25712;
        strDataDir = "testnet";
	// CBlock(hash=00003845b6cba6a72017f62f5299ecfbb832a4675082543d2db1e091b37a4b80, ver=1, pow_hash=00003845b6cba6a72017f62f5299ecfbb832a4675082543d2db1e091b37a4b80, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199186, nBits=1f00ffff, nNonce=57246, vtx=1)
  	//  Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//    CTxOut(empty)
  	//  vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
	genesis.nTime  = 1450199186;
	genesis.nNonce = 57246;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00003845b6cba6a72017f62f5299ecfbb832a4675082543d2db1e091b37a4b80"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,  112);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,  196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,  240);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

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
        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0x5b;
        pchMessageStart[2] = 0xfb;
        pchMessageStart[3] = 0xaf;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 5);
	// CBlock(hash=005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba, ver=1, pow_hash=005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199187, nBits=2007ffff, nNonce=33, vtx=1)
  	//   Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//    CTxOut(empty)
  	//   vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 33;
	genesis.nTime  = 1450199187;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18555;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba"));

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
