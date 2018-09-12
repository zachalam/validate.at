#include <validate.hpp>

namespace Validate {
    using namespace eosio;
    using std::string;

    class Proofs : public contract {
        using contract::contract;

        public:
            Proofs(account_name self):contract(self) {}

            //@abi action
            void add(account_name account, uint64_t hashVal) {
                // verify account.
                require_auth(account);

                proofIndex proofs(_self,_self);
                proofs.emplace(account,[&](auto& proof){
                    proof.account_name = account;
                    proof.hashVal = hashVal;
                });
            }

            //@abi action
            void getproof(uint64_t hashVal) {
                proofIndex proofs(_self,_self);
                auto theProof = proofs.find(hashVal);
                eosio_assert(theProof != proofs.end(), "Proof not found");
                print("Valid proof");
            }

        private:

            //@abi table proof i64
            struct proof {
                uint64_t account_name;
                uint64_t hashVal;

                uint64_t primary_key() const { return hashVal; }
                EOSLIB_SERIALIZE(proof,(account_name)(hashVal))
            };

            typedef multi_index<N(proof), proof> proofIndex;
    };

    EOSIO_ABI(Proofs,(add)(getproof))
}