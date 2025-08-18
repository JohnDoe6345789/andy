#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int64_t IOTC_Session_Read(int64_t sid, void *buf, int64_t size, int64_t timeout, int32_t flags);
int64_t IOTC_sCHL_shutdown(int64_t ssl);

/* Globals used to simulate stack guard */
void *__stack_chk_guard = (void*)0x1;
static int stack_fail_called;
void __stack_chk_fail(void)
{
    stack_fail_called = 1;
}

/* Stub and tracking for IOTC_Session_Read_Check_Lost_Data_And_Datatype */
static int64_t stub_read_ret;
static int modify_guard;
int64_t IOTC_Session_Read_Check_Lost_Data_And_Datatype(
    int64_t sid, void *buf, int64_t size, int64_t timeout,
    unsigned char *lost, unsigned char *datatype, int32_t flags,
    int32_t unused)
{
    (void)sid; (void)buf; (void)size; (void)timeout;
    (void)lost; (void)datatype; (void)flags; (void)unused;
    if (modify_guard)
        __stack_chk_guard = (void*)((uintptr_t)__stack_chk_guard + 1);
    return stub_read_ret;
}

/* Stubs for SSL/bio helpers */
int32_t *tutk_third_BIO_get_data(void *bio)
{
    return (int32_t *)bio;
}
void *tutk_third_SSL_get_rbio(int64_t ssl)
{
    return (void *)ssl;
}
static int32_t ssl_shutdown_ret;
int32_t tutk_third_SSL_shutdown(int64_t ssl)
{
    (void)ssl;
    return ssl_shutdown_ret;
}
static int32_t ssl_error_ret;
int32_t tutk_third_SSL_get_error(int64_t ssl, int32_t ret)
{
    (void)ssl; (void)ret;
    return ssl_error_ret;
}
void TUTK_LOG_MSG(int level, const char *module, int type,
                  const char *fmt, const char *func,
                  int32_t sid, int32_t chID, int32_t ret)
{
    (void)level; (void)module; (void)type;
    (void)fmt; (void)func; (void)sid; (void)chID; (void)ret;
}
static int64_t translate_err_ret;
int64_t translate_Error(int32_t ret, int64_t ssl)
{
    (void)ssl;
    return translate_err_ret ? translate_err_ret : ret;
}

/* Tests for IOTC_Session_Read */
static void test_read_no_guard_change(void)
{
    stub_read_ret = 0;
    modify_guard = 0;
    stack_fail_called = 0;
    int64_t r = IOTC_Session_Read(5, NULL, 10, 20, 0);
    assert(r == 0);
    assert(stack_fail_called == 0);
}

static void test_read_failure_calls_stack_fail(void)
{
    stub_read_ret = 1;
    modify_guard = 0;
    stack_fail_called = 0;
    (void)IOTC_Session_Read(5, NULL, 10, 20, 0);
    assert(stack_fail_called == 1);
}

static void test_read_guard_change_triggers_fail(void)
{
    stub_read_ret = 0;
    modify_guard = 1;
    stack_fail_called = 0;
    (void)IOTC_Session_Read(5, NULL, 10, 20, 0);
    assert(stack_fail_called == 1);
}

/* Tests for IOTC_sCHL_shutdown */
static void test_shutdown_no_existing(void)
{
    int32_t bio[23] = {0};
    bio[21] = 0;
    ssl_shutdown_ret = 1;
    translate_err_ret = 0;
    int64_t r = IOTC_sCHL_shutdown((int64_t)bio);
    assert(r == 0);
    assert(bio[20] == 1);
    assert(bio[22] == 0);
}

static void test_shutdown_existing_success(void)
{
    int32_t bio[23] = {0};
    bio[21] = 1;
    ssl_shutdown_ret = 1;
    ssl_error_ret = 0;
    translate_err_ret = 0;
    int64_t r = IOTC_sCHL_shutdown((int64_t)bio);
    assert(r == 0);
    assert(bio[22] == 1);
}

static void test_shutdown_existing_error(void)
{
    int32_t bio[23] = {0};
    bio[21] = 1;
    ssl_shutdown_ret = -1;
    ssl_error_ret = -5;
    translate_err_ret = -5;
    int64_t r = IOTC_sCHL_shutdown((int64_t)bio);
    assert(r == -5);
    assert(bio[22] == 1);
}

int main(void)
{
    test_read_no_guard_change();
    test_read_failure_calls_stack_fail();
    test_read_guard_change_triggers_fail();
    test_shutdown_no_existing();
    test_shutdown_existing_success();
    test_shutdown_existing_error();
    printf("All tests executed\n");
    return 0;
}
