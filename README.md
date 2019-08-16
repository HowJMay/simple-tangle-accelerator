# Instruction 
This is a repo for simple tangle-accelerator usage.
Current we have two following simple operations.
1. send transfer
2. receive transfer message

## Send Transfer
To build program for sending transfer
```
$ bazel build //accelerator:transfer
```

**usage:**
```
$ ./transfer <message> <tag>
```

## Receive Transfer Message
To build program for receiving transfer message. We use `tag` for searching transfer messages.
```
$ bazel build //accelerator:transfer
```

**usage:**
```
$ ./recv_txn <tag>
```