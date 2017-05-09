#include <stdio.h>		/* printf(), fprintf()に必要 */
#include <sys/socket.h> /* socket(),connect(),send(),recv()に必要 */
#include <arpa/inet.h>  /* sockaddr_in, inet_addr()に必要 */
#include <stdlib.h>		/* atoi()に必要 */
#include <string.h>		/* memset()に必要 */
#include <unistd.h>		/* close()に必要 */

#define MAXPENDING 5	/* 受信バッファのサイズ */

void DieWithError(char *errorMessage);	/* エラー処理関数 */
void HandleTCPClient(char clntSocket);	/* TCPクライアント処理関数 */

int main(int argc, char *argv[])
{
	int servSock;						/* サーバのソケットディスクリプタ */
	int clntSock;						/* クライアントのソケットディスクリプタ */
	struct sockaddr_in echoServAddr;	/* ローカルアドレス */
	struct sockaddr_in echoClntAddr;	/* クライアントアドレス */
	unsigned short echoServPort;		/* サーバポート */
	unsigned int clntLen;				/* クライアントのアドレス構造体の長さ */

	if ((argc != 2))		/* 引数の数が正しいか確認 */
	{
		fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
		exit(1);
	}

	echoServPort = atoi(argv[1]);		/* 1つ目の引数：ローカルポート */

	/* 着信接続用のソケットを作成 */
	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	/* ローカルのアドレス構造体を作成 */
	memset(&echoServAddr, 0, sizeof(echoServAddr));		/* 構造体に0を埋める */
	echoServAddr.sin_family = AF_INET;					/* インターネットアドレスファミリ */
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);	/* ワイルドカードを使用 */
	echoServAddr.sin_port = htons(echoServPort);		/* ローカルポート */

	/* ローカルアドレスへバインド */
	if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("bind() failed");

	/* 「接続要求をリスン中」というマークをソケットに付ける */
	if (listen(servSock, MAXPENDING) < 0)
		DieWithError("listen() failed");

	for (;;)	/* 処理を繰り返し実行 */
	{
		/* 入出力パラメータのサイズをセット */
		clntLen = sizeof(echoClntAddr);

		/* クライアントからの接続要求を待機 */
		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,
											&clntLen)) < 0)
			DieWithError("accept() failed");

		/* clntSockはクライアントに接続済み */

		printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

		HandleTCPClient(clntSock);
	}
	/* この部分には到達しない */
}
