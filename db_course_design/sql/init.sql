create table user_table(
    id          integer primary key,
    username    varchar unique,
    password    varchar
);

create table quzl_table(
    id          integer primary key,
    quzlname    varchar,
    ownerid     integer
);

create table quz_table(
    id          integer primary key,
    quzcontent  varchar,
    quzlid      integer
);

create table option_table(
    id          integer primary key,
    optcontent  varchar,
    quzid       integer
);

create table answer_table(
    id          integer primary key,
    cnt         integer,
    optid       integer
);

问卷: 1 2

问题: 1->1 2->1 3->1 4->2 