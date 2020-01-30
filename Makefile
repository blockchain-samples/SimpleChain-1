compile:
	g++  main.cpp Block.cpp Blockchain.cpp Wallet.cpp sha256.cpp Transaction.cpp ECDSA.cpp Transactioninput.cpp TransactionOutput.cpp -lcrypto
clean:
	rm ./a.out
