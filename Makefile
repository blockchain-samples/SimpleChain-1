compile:
	g++  main.cpp Block.cpp Blockchain.cpp Wallet.cpp sha256.cpp Transaction.cpp Transactioninput.cpp TransactionOutput.cpp RSAHelper.cpp -lcrypto
clean:
	rm ./a.out
