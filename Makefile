compile:
	g++ SimpleChain.cpp Transaction.cpp TransactionInput.cpp TransactionOutput.cpp Block.cpp Blockchain.cpp Wallet.cpp MerkleRoot.cpp sha256.cpp RSAHelper.cpp -lcrypto -o SimpleChain
clean:
	rm ./SimpleChain
