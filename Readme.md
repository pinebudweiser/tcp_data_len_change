# :speech_balloon: tcp_data_len_change

Comment: TCP Data ������ �����϶�(���� ����).<br>
Argument Format : tcp_data_len_change \<from string\> \<to string\> <br>
Table command : iptables -A OUTPUT -j NFQUEUE, iptables -A INPUT -j NFQUEUE

## :green_book: ������ ������ ���� �ϱ� ���� ���
  - ������(payload)�� ���� �ϴ��� Ȯ���Ѵ�.
  - ������ �������� ���� �� ����� ���ڿ��� �ִ��� Ȯ���Ѵ�.
  
�������� : IP ����� `TotalLength`�� ������ ������ ��ŭ ������ �����Ͽ� ���� ��Ŷ���� ����� �ش��ϸ� �������� ������?<br>
�������� : ������ �����ε������� ���� �ǿ����ڸ� ���� �Ҵ�� �������� ��

## :green_book: ���Ǵ� ���

- STL Map<key,value> : Ű�� �ϳ��� �÷ο� Ŭ������ ����, value�� SEQ, ACK ����ü�� �����Ѵ�.
- INPUT, OUTPUT ü�� �� ��Ŷ ����� ������ ������ Map Ʈ���� ������ �Ѵ�.

## :green_book: ������ ����

- IP Class, TCP Class ���� ���踦 ��� �־� ����.. ���?
- �ν��Ͻ��� ���� �������� �ʱ�ȭ ���.
- ������ �����ε������� ���� �ǿ����ڸ� ���� �Ҵ�� �������� �޴� ���.

## ���� ���

- ��������� ��� ��� �ϰ� �־ üũ���� ��� �� ��..?
- Map������ Key�� Value�� ��� �� ��?